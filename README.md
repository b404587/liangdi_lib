liangdi
=======
1、检查计算机上是否已经有SSH key:
cd ~/.ssh

2、创建个新的SSH key
ssh-keygen -t rsa -C "your_email@youremail.com"

3、直接按下“enter”键即可，然后输入密码
4、一切顺利的话，你可以查看下c:\Users\Administrator\.ssh\id_rsa.pub文件，复制里面的key码

5、增加ssh key到github上
留意并不需要填写title，github会自动生成，直接把复制的key黏贴到key输入框确定即可

git@github.com:b404587/liangdi_lib.git