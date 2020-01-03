# CMu6Box
A music box based on terminal.



## Build

### Requirements

- Ncurses library for CUI
- Qt dev tools for multimedia



### Install The Ncurses Library

```sh
sudo apt-get install libncurses5-dev libncursesw5-dev
```



### Build The Qt Application

```sh
mkdir build && cd build
qmake ../Myplayer.pro
make
```



### Run It

```sh
./Myplayer
```



![welcome](img/welcome.png)



## Character User Interface

### Playing && Pause

![playing](img/playing.png)

![pause](img/pause.png)



### Play List && Edit

![playlist](img/playlist.png)

![playlist_edit](img/playlist_edit.png)



### Song List && Edit

![songlist](img/songlist.png)

![songlist_edit](img/2.png)



### Directory Walking

![walk_dir](img/walk_dir.gif)



### Setting

![setting](img/setting.png)

![zh_cn_sup](img/zh_cn_sup.png)