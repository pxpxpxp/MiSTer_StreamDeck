#define main mini_program_main
#include "streamdeck-mini.c"
#undef main
#include <assert.h>

static int fired;
static void capture(int key,double now){(void)now;assert(key==4);fired++;}
static void arm_inputs(void){memset(&inputs,0,sizeof inputs);memset(inputs.armed,1,sizeof inputs.armed);}

static void protocol_tests(void){
  assert(!selftest());
  uint8_t report[1024],payload[1008],states[6];
  memset(payload,0x5a,sizeof payload);
  for(int key=0;key<6;key++)for(unsigned chunk=0;chunk<20;chunk++){
    packet(report,key,chunk,payload,chunk==19?102:1008,chunk==19);
    assert(report[0]==2&&report[1]==1&&report[2]==chunk&&report[3]==0);
    assert(report[4]==(chunk==19)&&report[5]==key+1);
    for(int i=6;i<16;i++)assert(!report[i]);
    assert(!memcmp(report+16,payload,chunk==19?102:1008));
    if(chunk==19)for(int i=118;i<1024;i++)assert(report[i]==0);
  }
  uint8_t raw[65]={1,1,0,1,0,1,0};
  assert(!decode(raw,7,states)&&!decode(raw,65,states));
  for(int n=0;n<65;n++)if(n!=7)assert(decode(raw,n,states)==-1);
  raw[0]=2;assert(decode(raw,7,states)==-1);raw[0]=1;
  for(int k=1;k<=6;k++){raw[k]=2;assert(decode(raw,65,states)==-1);raw[k]=0;}
  uint8_t f[17];brightness_report(f,-1);assert(f[5]==0);
  brightness_report(f,999);assert(f[5]==100);
  for(int i=6;i<17;i++)assert(f[i]==0);
  puts("PASS: all Mini keys, all 20 BMP chunks, report padding, malformed input and brightness bounds");
}

static void page_tests(void){
  for(int p=0;p<PAGES;p++){page_configs[p]=newconfig();assert(page_configs[p]);}
  cfg=page_configs[0];active_page=0;reset_usb_state();
  for(int p=0;p<PAGES;p++)page_configs[p]->keys[5].action=NEXT_PAGE;
  page_configs[4]->keys[3].action=BACK_PAGE;
  page_configs[0]->keys[4].action=CYCLE;
  uint8_t state[KEYS]={0};
  for(int page=0;page<PAGES;page++){
    arm_inputs();state[5]=1;handle_input(state,10+page,capture);
    assert(active_page==page&&uploads[5].wanted==1&&restore[5]==0);
    enqueue(&queue,0);state[5]=0;handle_input(state,10.1+page,capture);
    assert(active_page==(page+1)%PAGES&&queue.count==0);
  }
  arm_inputs();state[4]=1;handle_input(state,20,capture);
  state[4]=0;handle_input(state,20.1,capture);assert(fired==1&&active_page==0);
  state[4]=1;handle_input(state,21,capture);handle_holds(22.01,capture);
  assert(active_page==NAV_PAGE&&!inputs.armed[4]);
  state[4]=0;handle_input(state,22.1,capture);assert(fired==1);
  switch_page(4);arm_inputs();state[3]=1;handle_input(state,23,capture);
  assert(active_page==4&&uploads[3].wanted==1&&restore[3]==0);
  state[3]=0;handle_input(state,23.1,capture);assert(active_page==0);
  /* Held keys during a page change must not produce a new press. */
  arm_inputs();state[0]=1;inputs.down[0]=1;switch_page(3);
  assert(!inputs.armed[0]);handle_input(state,24,capture);assert(!inputs.armed[0]);
  state[0]=0;handle_input(state,24.1,capture);assert(inputs.armed[0]);
  int pipes[2];assert(!pipe(pipes));keyboard_fd=pipes[1];
  cfg->keys[0].action=UP_BUTTON;arm_inputs();state[0]=1;handle_input(state,25,capture);
  assert(uploads[0].wanted==1&&restore[0]==0);
  struct input_event event[2];assert(read(pipes[0],event,sizeof event)==sizeof event);
  assert(event[0].code==KEY_UP&&event[0].value==1);
  state[0]=0;handle_input(state,30,capture);assert(uploads[0].wanted==0);
  assert(read(pipes[0],event,sizeof event)==sizeof event);assert(!event[0].value);
  keyboard_close();close(pipes[0]);
  /* Update All completion must be delivered to Home/key 4 while hidden. */
  page_configs[0]->keys[3].action=UPDATE_ALL;strcpy(page_configs[0]->keys[3].target,"Scripts/update_all.sh");
  active_page=4;cfg=page_configs[4];reset_usb_state();
  pid_t child=fork();assert(child>=0);if(!child)_exit(0);
  script_pid=child;script_key=3;script_action=UPDATE_ALL;strcpy(script_target,"Scripts/update_all.sh");script_started=nowtime();
  page_uploads[0][3].wanted=1;
  for(int i=0;i<200&&script_pid>0;i++){reap_page_script(nowtime(),0);usleep(1000);}
  assert(script_pid<0&&page_uploads[0][3].wanted==3&&uploads[3].wanted==0);
  switch_page(0);assert(uploads[3].wanted==3);
  assert(next_brightness(CYCLE,25)==50&&next_brightness(CYCLE,100)==10);
  for(int p=0;p<PAGES;p++){freeconfig(page_configs[p]);page_configs[p]=NULL;}cfg=NULL;
  puts("PASS: five-page wrap, release feedback, hold shortcut, held-key rearming and hidden Home updater completion");
}

static void package_tests(const char *root){
  assert(!textset(configpath,sizeof configpath,root));
  char *slash=strrchr(configpath,'/');assert(slash);
  assert(!textset(assets,sizeof assets,root));*strrchr(assets,'/')=0;
  assert(strlen(assets)+6<sizeof assets);strcat(assets,"/icons");
  struct config *pages[PAGES]={readconfig(1)};assert(pages[0]);assert(!load_pages(pages));
  assert(pages[0]->keys[3].action==UPDATE_ALL&&!strcmp(pages[0]->keys[3].target,"Scripts/update_all.sh"));
  for(int p=0;p<PAGES;p++){
    assert(pages[p]->keys[5].action==NEXT_PAGE);
    for(int k=0;k<KEYS;k++)for(int state=0;state<3;state++){
      struct image *im=&pages[p]->keys[k].images[state];assert(im->frame_count>0);
      for(unsigned f=0;f<im->frame_count;f++)assert(validbmp(im->frames[f].data,im->frames[f].size));
    }
  }
  /* Serialize one whole frame and verify all chunks concatenate exactly. */
  cfg=pages[0];page_configs[0]=cfg;reset_usb_state();
  for(int k=0;k<KEYS;k++){uploads[k].current=0;uploads[k].finished=1;}
  uploads[0].finished=0;
  int pair[2];assert(!pipe(pair));uint8_t report[1024],assembled[19254];size_t used=0;
  for(int n=0;n<20;n++){
    assert(upload_step(pair[1])==1);assert(read(pair[0],report,sizeof report)==1024);
    size_t count=sizeof assembled-used;if(count>1008)count=1008;
    assert(report[2]==n&&report[5]==1&&report[4]==(n==19));memcpy(assembled+used,report+16,count);used+=count;
  }
  assert(used==sizeof assembled&&!memcmp(assembled,cfg->keys[0].images[0].frames[0].data,used));
  close(pair[0]);close(pair[1]);cfg=NULL;page_configs[0]=NULL;
  for(int p=0;p<PAGES;p++)freeconfig(pages[p]);
  puts("PASS: real five-page artwork, first-page updater target, bounded BMP validation and complete image serialization");
}

int main(int argc,char **argv){protocol_tests();page_tests();if(argc>1)package_tests(argv[1]);return 0;}
