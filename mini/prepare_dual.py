"""Bundle isolated MK.2 and Mini services without mixing configurations."""
import argparse, shutil
from pathlib import Path
from dual_support import patch_updater_lock

def prepare(base,mini,output):
    shutil.copytree(base/'Scripts',output/'Scripts',dirs_exist_ok=True)
    shutil.copytree(mini/'Scripts',output/'Scripts',dirs_exist_ok=True)
    app=output/'Scripts/.config/streamdeck'
    source=app/'source/streamdeck.c'
    text=patch_updater_lock(source.read_text())
    text=text.replace('#define VERSION "1.0.0"','#define VERSION "1.0.0 Dual 1.0.0"')
    # Match only the 15-key family; identity queries on other devices are read-only.
    text=text.replace('int fd = open(g.gl_pathv[i], O_RDWR | O_NONBLOCK);','int fd = open(g.gl_pathv[i], O_RDONLY | O_NONBLOCK | O_CLOEXEC);')
    old='''      snprintf(path, 128, "%s", g.gl_pathv[i]);
      chosen = fd;
      break;'''
    new='''      close(fd);
      fd=open(g.gl_pathv[i],O_RDWR|O_NONBLOCK|O_CLOEXEC);
      if(fd<0)continue;
      if(flock(fd,LOCK_EX|LOCK_NB)||ioctl(fd,RAWINFO,&info)||info.bustype!=BUS_USB||
         (uint16_t)info.vendor!=0x0fd9||((uint16_t)info.product!=0x0080&&(uint16_t)info.product!=0x00a5)){
        close(fd);continue;
      }
      snprintf(path, 128, "%s", g.gl_pathv[i]);
      chosen = fd;
      break;'''
    assert text.count(old)==1;text=text.replace(old,new)
    source.write_text(text)
    for name in ['LICENSE.txt','ARTWORK_CREDITS.txt']:
        shutil.copy2(base/name,output/name)
    for name in ['Mini_Guide.html','MINI_LAYOUT.json']:
        if (mini/name).exists():shutil.copy2(mini/name,output/name)
    (output/'README.txt').write_text(Path(__file__).with_name('DUAL_README.md').read_text())
    for operation in ['Enable','Disable']:
        # Keep boot edits serial; a failure must remain visible to the user.
        script=f'''#!/bin/sh
set -eu
sh /media/fat/Scripts/StreamDeck_{operation}.sh
sh /media/fat/Scripts/StreamDeck_Mini_{operation}.sh
echo 'Both Stream Deck services {operation.lower()}d.'
'''
        (output/'Scripts'/f'StreamDeck_Both_{operation}.sh').write_text(script)
    for p in (output/'Scripts').rglob('*.sh'):p.chmod(0o755)
    print('Prepared Dual v1.0.0: isolated services and shared Update All lock')

if __name__=='__main__':
    p=argparse.ArgumentParser();p.add_argument('base',type=Path);p.add_argument('mini',type=Path);p.add_argument('output',type=Path)
    a=p.parse_args();prepare(a.base,a.mini,a.output)
