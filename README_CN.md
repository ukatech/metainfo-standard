# 伪春菜用metainfo标准  

## 什么是metainfo？  

metainfo是一种用于描述伪春菜的可扩展标准，它包含了web应用所需要的基本信息  

## 为什么用metainfo？  

以GCS为例
考虑现版本的GCS所需求的信息架构，当你需要客制化CGS中你的ghost的预览图时，你需要在`shell/master`存放一或两个用户根本用不到的apng文件  
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
/.ukagaka
    ├── descript.txt
    ├── /preview
    │   ├── sakura.png
    │   └── kero.png
    ├── icon.png
    ├── /links
    └── /infos
```

或

```filetree
/.ukagaka
    └── jump_to.txt
```

#### 文件介绍  

- `descript.txt`：ghost的描述文件，用于在web应用中提供基础信息  
- `preview`：ghost的预览图文件夹，用于在web应用中提供预览图（不强制要求）  
- `icon.png`：ghost的图标文件，用于在web应用中提供图标（不强制要求）  
- `links`：ghost的链接文件夹，用于在web应用中提供可拓展的相关链接信息（不强制要求）
- `infos`：ghost的信息文件夹，用于在web应用中提供可拓展的其他信息（不强制要求）
- `jump_to.txt`：元信息文件夹跳转文件，用于重定向到新的元信息文件夹（只在当前文件夹废弃时使用）  

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
uuid,R5dVNluBvKjtQqjP0dAuoA==
sakura.name,橘花
kero.name,斗和
has_terms,1
icon,https://github.com/Taromati2/other/raw/master/discord_app/kikka_eye_open.png
homeurl,https://raw.githubusercontent.com/Taromati2/stable-mirror/master/Taromati2/
craftman,8 and other contributors
craftmanurl,https://github.com/Taromati2/Taromati2/blob/master/docs/CONTRIBUTORS.md
languages,Simplified Chinese	//,Japanese,English may be available in future
```

任何非`://`开头的`//`直至行尾都会被视为注释，不应被解析  
`//meta info`作为开头是必须的  
以下选项必须：  
`type`：类型（以便日后标准拓展），必须为`ghost`  
`name`：名称  
`craftman`：制作者  
`craftmanurl`：制作者链接  
`uuid`：唯一标识符，详见[UUID标准](#uuid)  
`languages`：ghost支持的自然语言，如有多个，用`,`分隔  
当`type`为`ghost`时，以下选项必须：  
`sakura.name`：使魔`\0`的名称  
考虑到ghost不一定有使仆，所以`kero.name`可选（非必须）：  
`kero.name`：使仆`\1`的名称（若有多个使仆，可以用`kero1.name`、`kero2.name`等等来区分）  

非必须：
`has_terms`：是否有条款([`terms.txt`](https://ssp.shillest.net/ukadoc/manual/manual_directory.html))（0为否，1为是，不写默认0）  
`icon`：图标链接（不写默认为metainfo文件夹中的`icon.png`（若文件存在））  
`uuid_base`：用于防止uuid碰撞的uuid基础（详见[UUID标准](#uuid)）  

##### `links`

在`links`文件夹中，你可以存放任意数量的txt文件来存放相关链接信息，标准中规定（但非必须）的文件有：

- `mirror_repo.txt`：若你的ghost的文件内容不在此仓库进行更新，你可以在此文件中写入你的镜像仓库链接  
  链接应该是一个github仓库链接  
- `nar_release_repo.txt`：若你的ghost的nar文件不在此仓库进行发布，你可以在此文件中写入你的nar发布仓库链接  
  链接应该是一个github仓库链接

以上文件的内容可以是单个url配上多个空行结尾，如这样  

**nar_release_repo.txt**

```txt
https://github.com/Taromati2/package-factory


```

也可以是更为复杂的内容，带有更多的信息以及可选的注释  
在这种情况下，以上文件的内容都应该是`UTF8`编码并且任何非`://`开头的`//`直至行尾都会被视为注释，不应被解析  

**nar_release_repo.txt**

```txt
//a info file to tell the web app where to find the nar release repo
link, https://github.com/Taromati2/package-factory
nar_file_name, Taromati2.nar  //the nar file name

```

在这种情况下，`link`字段是必须的，而其他字段是可选的。  
`nar_file_name`字段在`nar_release_repo.txt`中用于告知web应用应该将repo的release中的哪个nar文件视为ghost的nar文件，这在一个release中有多个nar文件的情况下非常有用  

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
metainfo,https://raw.githubusercontent.com/Taromati2/Taromati2/master/.ukagaka/
githubrepo,https://github.com/Taromati2/Taromati2
```

没有metainfo的ghost可以通过这种方式追加metainfo和uuid  

## uuid

考虑到同名ghost或同ghost的不同分支版本可能会存在，所以uuid是必须的  
web应用可以通过uuid来区分实际上不同的同名ghost  

### uuid生成  

若你对uuid原理不关心，可以直接使用[uuid-genner](https://github.com/ukatech/metainfo-standard/tree/master/uuid-genner)生成uuid。  
要生成uuid，你需要先获得当前ghost的metainfo文件夹的url（以`UTF8`编码并且末尾无换行），然后对其进行md5加密，并对得到的二进制结果进行base64编码  
如`https://raw.githubusercontent.com/Taromati2/Taromati2/master/.ukagaka/`所生成的uuid为`R5dVNluBvKjtQqjP0dAuoA==`  
若ghost没有metainfo文件夹，uuid为二进制结果`0`的base64编码  
若metainfo中有`uuid_base`字段，将其直接添加到上一步得到的uuid前面  
`uuid_base`字段导致uuid不定长，但允许应用拒绝超过64位长度的uuid  

### uuid校验  

web应用应当在捕获到或接收到新的ghost时，对其uuid进行校验以检查信息合法性以避免任何混淆不同ghost的可能  
对uuid的校验应当访问metainfo文件夹并检查是否有`jump_to.txt`文件，若有则应用需要更新此ghost的metainfo文件夹的url和其uuid  
考虑到uuid可能因为metainfo文件夹地址的变更而变化，同一个ghost可能有多个历史uuid。  
应用对应用的特定ghost相关请求和逻辑构建中不应使用uuid来区分ghost，而是应当包含metainfo文件夹的url，以便uuid校验可以以最新的信息为准  
允许应用缓存ghost过去的uuid来实现快速ghost匹配，但应当在匹配失败时更新缓存内容  
若校验失败，应用应当拒绝此ghost的相关注册  

**重要：** 没有uuid的ghost不应和同名的有uuid的ghost混淆  
向已存在的ghost追加uuid的方法详见[通过ghost定向到metainfo文件夹](#通过ghost定向到metainfo文件夹)  

### 缺点

uuid只能保护已有uuid的ghost不被混淆或顶替，但无法保护历史中的无uuid的ghost不被顶替  
