# VLCDemo
基于libVLC的视频播放器（支持RTSP协议）        
VLC Media Player是一款优秀的播放器，大多数多媒体开发人员都使用过。 VLC是一款开源的、跨平台的、可扩展的、多媒体播放器、流媒体服务器及框架，可播放大多        数多媒体文件，以及DVD、音频CD、VCD及各类流媒体协议，现更名为VLC media player，最新版本为2.2.0。              
获取VLC开发所需要的SDK参考：http://blog.csdn.net/leixiaohua1020/article/details/42363079           
首先介绍程序中使用的三个结构体                  
libvlc_instance_t：代表一个libVLC的实例。              
libvlc_media_t：代表一个可以播放的媒体。         
libvlc_media_player_t：代表一个VLC媒体播放器（一个视频播放器播放一个视频）。注意VLC并不仅仅用于媒体播放。              
libVLC视频播放器的开发流程图如下所示：       
![image1](https://github.com/DaveBobo/VLCDemo/blob/master/Screenshots/vlc1.png)   
这里写图片描述                                  
函数讲解：                  
libvlc_new()：创建libvlc_instance_t。        
libvlc_media_new_location()：用于打开协议（我这里是打开使用VLC推的RTSP协议）          
libvlc_media_player_new_from_media()：创建libvlc_media_player_t。       
libvlc_media_player_set_hwnd();设置视频显示窗口           
libvlc_media_player_release()：释放libvlc_media_player_t      
libvlc_media_release()：释放libvlc_media_t。         
libvlc_release()：释放libvlc_instance_t。              
下面的函数控制媒体的播放、暂停和停止            
libvlc_media_player_play()：播放。                
libvlc_media_player_pause()：暂停。          
libvlc_media_player_stop()：停止。     
展示效果：                            
![image2](https://github.com/DaveBobo/VLCDemo/blob/master/Screenshots/vlc2.jpg)   
这里写图片描述                              
注意事项                   
创建libvlc_media_t有两种方法：libvlc_media_new_path()和libvlc_media_new_location()。简单描述一下这两个函数的区                           别：libvlc_media_new_location()用于打开协议，而libvlc_media_new_path()用于打开文件。因而传递给libvlc_media_new_path()的就是普通的文件路径            （绝对路径例如D:\xxx.flv，或者相对路径例如xxx.flv），而传递给libvlc_media_new_location()的就是协议地址（例如“udp://….”，“http://”）。但是这里          有一点需要注意，在VLC中“文件”也属于一种广义上的“协议”。因此使用libvlc_media_new_location()也可以打开文件，但是必须在文件路径前面加上“文件协议”的标记“file:///”。例如打开“F:\movie\cuc_ieschool.flv”下的视频，实际使用的代码如下所示。            
libvlc_media_new_location (inst, "file:///F:\\movie\\cuc_ieschool.flv");           
此外，VLC还支持很多“神奇”的协议，比如输入“screen://”协议就可以进行屏幕录制，代码如下。             
libvlc_media_new_location (inst, "screen://");                         
【视音频图像技术干货，FFmpeg流媒体、OpenCV图像及深度学习技术探索，开源项目推荐，还有更多职场规划】欢迎关注我的微信公众号，扫一扫下方二维码或者长按识别二维码。                    
<div align=center><img src="https://github.com/DaveBobo/RtspPlayer/blob/master/Screenshots/wx.jpg"/></div>
