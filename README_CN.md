# 伪春菜用metainfo标准  

## 什么是metainfo？  

metainfo是一种用于描述伪春菜的可扩展标准，它包含了web应用所需要的伪春菜的基本信息  

## 为什么用metainfo？  

以GCS为例
考虑现版本的GCS所需求的信息架构，当你需要客制化CGS中你的伪春菜的预览图时，你需要在`shell/matser`存放一或两个用户根本用不到的apng文件  
这不仅扰乱了项目布局，也让不同用处的文件混在一起，不利于项目维护  
再考虑现有版本的GCS所提供的跳转功能，它只能跳转至作者的主页，缺乏自定义和客制化的功能  
metainfo的出现就是为了解决这些问题  

## metainfo的结构标准  

### 存贮位置  

我们推荐将metainfo文件夹存放在任何非本地ghost文件夹内的云存贮目录中用于随时更新相关信息并且不占据用户本地存储空间  
如果你的ghost在github上有单独的项目，我们推荐将metainfo文件夹存放在项目的默认分支的根目录下  
例如`https://github.com/Taromati2/Taromati2`，按照标准，metainfo文件夹应该存放在`https://github.com/Taromati2/Taromati2/tree/master/.ukagaka`（这里的`master`是默认分支）  

### 相关tag  

如果你的ghost在github上有单独的项目，并且设立了metainfo文件夹，我们推荐给项目添加`ukagaka-ghost`标签以便一些web应用能够识别到你的ghost  

### 文件结构  

```filetree
.ukagaka
    ├── descript.txt
    ├── /preview
    │   ├── sakura.png
    │   └── kero.png
    ├── icon.png
    ├── /links
    └── /infos
```

#### 文件介绍  

- `descript.txt`：伪春菜的描述文件，用于在web应用中提供基础信息  
- `preview`：伪春菜的预览图文件夹，用于在web应用中提供预览图（不强制要求）  
- `icon.png`：伪春菜的图标文件，用于在web应用中提供图标（不强制要求）  
- `links`：伪春菜的链接文件夹，用于在web应用中提供可拓展的相关链接信息（不强制要求）
- `infos`：伪春菜的信息文件夹，用于在web应用中提供可拓展的其他信息（不强制要求）

#### 文件内容介绍

##### `preview`

在`preview`文件夹中，你可以存放任意数量的png文件，但是我们推荐你至少存放两个png文件，分别命名为`sakura.png`和`kero.png`  
如果你想提供动态预览图，你可以将动态预览图存放在`preview`文件夹中，分别命名为`sakura.apng`和`kero.apng`  
如果你的ghost有多个kero，你可以这样追加命名：`kero1.png`、`kero2.png`、`kero3.png`等等  

对于web应用开发者来说，你需要注意的是整个`preview`文件夹的提供是可选的，其中的任何内容也都是可选的  

##### `descript.txt`

`descript.txt`文件的内容是强制要求的，它的内容应该是`UTF8`编码，并遵循这样的格式：  

```txt
//meta info
type,ghost
name,Taromati2
//uuid,XXX
sakura.name,橘花
kero.name,斗和
has_terms,1
icon,https://github.com/Taromati2/other/raw/master/discord_app/kikka_eye_open.png
homeurl,https://raw.githubusercontent.com/Taromati2/stable-mirror/master/Taromati2/
craftman,8 and other contributors
craftmanurl,https://github.com/Taromati2/Taromati2/blob/master/docs/CONTRIBUTORS.md
languages,Simplified Chinese	//,Japanese,Engilsh may be available in future
```

任何非`://`开头的`//`直至行尾都会被视为注释，不应被解析  
`//meta info`作为开头是必须的  
以下选项必须：
`type`：类型（以便日后标准拓展），必须为`ghost`  
`name`：名称  
`craftman`：制作者  
`craftmanurl`：制作者链接  
`languages`：ghost支持的自然语言，如有多个，用`,`分隔
当`type`为`ghost`时，以下选项必须：
`sakura.name`：使魔`\0`的名称
考虑到ghost不一定有使仆，所以`kero.name`可选（非必须）：
`kero.name`：使仆`\1`的名称（若有多个使仆，可以用`kero1.name`、`kero2.name`等等来区分）

非必须：
`has_terms`：是否有条款（0为否，1为是，不写默认0）  
`icon`：图标链接（不写默认为metainfo文件夹中的`icon.png`（若文件存在））  

##### `links`

在`links`文件夹中，你可以存放任意数量的txt文件来存放相关链接信息，标准中规定（但非必须）的文件有：

- `mirror_repo.txt`：若你的ghost的文件内容不在此仓库进行更新，你可以在此文件中写入你的镜像仓库链接  
  链接应该是一个github仓库链接  
- `nar_release_repo.txt`：若你的ghost的nar文件不在此仓库进行发布，你可以在此文件中写入你的nar发布仓库链接  
  链接应该是一个github仓库链接

其余的文件留给第三方进行标准拓展，日后不排除新增标准规定文件的可能性  
推荐第三方拓展的文件若不是通用的，应该在文件名中加入web应用的名字或缩写，如`GCS_link.txt`

##### `infos`

在`infos`文件夹中，你可以存放任意数量的txt文件来存放web应用需要的相关信息  

## 通过ghost定向到metainfo文件夹  

鼓励ghost开发者在`ghost/descript.txt`中写入`metainfo`字段并后附metainfo文件夹的url，以便特定应用可以通过ghost定向到metainfo文件夹
也可在`ghost/descript.txt`中写入`githubrepo`字段并后附github项目的url，两者效果相等且可同时存在  
例子：

```txt
//...
mousecursor.grip,./img/curs/hand_grip.cur
//
metainfo,https://github.com/Taromati2/Taromati2/tree/master/.ukagaka
githubrepo,https://github.com/Taromati2/Taromati2
```