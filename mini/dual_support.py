"""Apply the same cross-device updater lock to both native launchers."""
def patch_updater_lock(source):
    def replace(old,new):
        nonlocal source
        assert source.count(old)==1,old
        source=source.replace(old,new)
    replace('static pid_t script_pid = -1;', 'static pid_t script_pid = -1;\nstatic int script_update_lock = -1;')
    anchor='  int out = open(logpath, O_CREAT | O_WRONLY | O_TRUNC, 0600);'
    replace(anchor,'''  /* Shared by the Mini and MK.2; never run two Update All jobs. */
  int updater_lock = -1;
  if (cfg->keys[key].action == UPDATE_ALL) {
    updater_lock = open("/tmp/mister_streamdeck_update_all.lock", O_CREAT | O_RDWR | O_CLOEXEC, 0600);
    if (updater_lock < 0) return -1;
    if (flock(updater_lock, LOCK_EX | LOCK_NB)) {
      close(updater_lock);
      logmsg("Update All is already running on another deck; request ignored");
      return -2;
    }
  }
'''+anchor)
    replace('  if (out < 0) {\n    logmsg("Cannot open script log:', '  if (out < 0) {\n    if (updater_lock >= 0) close(updater_lock);\n    logmsg("Cannot open script log:')
    replace('  if (pid < 0) {\n    logmsg("Script fork failed:', '  if (pid < 0) {\n    if (updater_lock >= 0) close(updater_lock);\n    logmsg("Script fork failed:')
    replace('  setpgid(pid, pid);', '  script_update_lock = updater_lock;\n  setpgid(pid, pid);')
    replace('  script_pid = -1;\n  script_key = -1;', '  if (script_update_lock >= 0) { close(script_update_lock); script_update_lock = -1; }\n  script_pid = -1;\n  script_key = -1;')
    return source
