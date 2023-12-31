# Ukagaka uses the metainfo standard

## What is metainfo?

metainfo is an extensible standard for describing ukagaka, which contains the basic information needed for web applications.

## Why use metainfo?

Take GCS ([Ghost Captor Sakura](http://buynowforsale.shillest.net/ghosts/)) as an example.  
Consider the information architecture required by the current version of GCS. When you need to customize the preview image of your ghost in CGS, you need to store one or two apng files in `shell/master` that the user won't even use.  
This not only disrupts the project layout, but also allows files with different uses to be mixed together, which is not conducive to project maintenance.  
Consider also the redirection provided by the current version of GCS, which only redirects to the author's home page and lacks customization.  
metainfo was created to solve these problems.

## Structural criteria for metainfo

### Storage location

We recommend storing the metainfo folder in any cloud storage directory that is not in the local ghost folder, to keep it up to date and avoid taking up local storage space for the user.  
If your ghost has a separate project on github, we recommend storing the metainfo folder in the root of the default branch of the project.  
For example, in `https://github.com/Taromati2/Taromati2`, the metainfo folder should be stored in `https://github.com/Taromati2/Taromati2/tree/master/.ukagaka` by default (where `master` is the default branch).

### Related tags

If your ghost has a separate project on GitHub and a metainfo folder, we recommend tagging the project with `ukagaka-ghost` so that some web applications can recognize your ghost.

### File structure

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

or

```filetree
/.ukagaka
    └── jump_to.txt
```

#### Introduction to the files  

- `descript.txt`: Ghost's description file, used to provide basic information in web applications  
- `preview`: Ghost's preview folder, used to provide preview images in web applications (optional)  
- `icon.png`: Ghost's icon file, used to provide icons in web applications (optional)  
- `links`: Ghost's links folder, used to provide expandable and relevant link information in web applications (optional)  
- `infos`: Ghost's information folder, used to provide expandable additional information in web applications (optional)  
- `jump_to.txt`: Jump file for redirecting to a new meta information folder (only used if the current folder is deprecated)

#### Files content description

##### `preview`

You can store any number of png files in the `preview` folder, but we recommend that you store at least two png files, named `sakura.png` and `kero.png` respectively  
If you want to provide dynamic previews, you can store them in the `preview` folder as `sakura.apng` and `kero.apng` respectively.  
If your ghost has more than one kero, you can add additional names like this: `kero1.png`, `kero2.png`, `kero3.png`, etc.

For web application developers, you need to note that the entire `preview` folder is optional and any content within it is also optional.

##### `descript.txt`

The contents of the `descript.txt` file are mandatory. It should be `UTF8` encoded and follow this format.

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

Any `//` that does not start with `://` will be treated as a comment, up to the end of the line, and should not be parsed.  
The beginning of the file must be `//meta info`

The following options are required:

`type`: Type, must be `ghost` (Included for later expansion of the standard)  
`name`: Name  
`craftman`: Author  
`craftmanurl`: Link to the author  
`uuid`: Unique identifier, see [UUID standard](#uuid) for details  
`languages`: The natural languages supported by ghost, separated by `,` if there are more than one  

When `type` is `ghost`, the following options are required:

`sakura.name`: The name of the sakura character `\0`.  
`kero.name` is optional, since not all ghosts have companion characters.  
`kero.name`: The name of the kero character `\1` (if there are multiple keros, they can be distinguished with `kero1.name`, `kero2.name`, etc.)  

The following options are not required:

`has_terms`: Whether or not there are terms([`terms.txt`](https://ssp.shillest.net/ukadoc/manual/manual_directory.html)) (0 for no, 1 for yes; default is 0 if not specified)  
`icon`: Icon link (If not specified, defaults to `icon.png` in the metainfo folder (if the file exists))  
`uuid_base`: uuid base for preventing uuid collisions (see [UUID standard](#uuid) for details)

##### `links`

In the `links` folder you can store as many txt files as you like to hold the relevant link information. The files specified (but not required) in the standard are:

- `mirror_repo.txt`: If the contents of your ghost files are not updated in this repository, you can write a link to your mirror repository in this file.  
  The link should be a github repository link.  
- `nar_release_repo.txt`: if your ghost's nar files are not released in this repository, you can write a link to your nar release repository in this file.  
  The link should be a github repository link.

The content of the above file can be a single url with multiple blank line endings, like this  

**nar_release_repo.txt**

```txt
https://github.com/Taromati2/package-factory


```

It can also be more complex, with more information and optional comments.  
In this case, the content of the above files should be `UTF8` encoded and any `//` that does not start with `://` up to the end of the line is considered a comment and should not be parsed.  

**nar_release_repo.txt**

```txt
//a info file to tell the web app where to find the nar release repo
link, https://github.com/Taromati2/package-factory
nar_file_name, Taromati2.nar  //the nar file name

```

In this case, the `link` field is required and the other fields are optional.  
The `nar_file_name` field is used in `nar_release_repo.txt` to tell the web application which nar file in the release of the repo should be considered as the ghost's nar file, which is useful in cases where there are multiple nar files in a release  

The rest of the files are left to third parties for standard extensions, and the possibility of adding new standard-specified files can be ruled out later.  
Recommended third-party extensions that are not generic should include the name of the web application or an abbreviation in the file name, e.g. `GCS_link.txt`

##### `infos`

In the `infos` folder you can store as many txt files as you need to hold information for web applications.  

## Directing to the metainfo folder via ghost

Ghost developers are encouraged to write a `metainfo` field in `ghost/descript.txt` followed by the url to the metainfo folder so that specific applications can be directed to the metainfo folder via ghost.
You can also write the `githubrepo` field in `ghost/descript.txt` followed by the url of the github project, both of which have the same effect for web app and can co-exist.  
Example:

```txt
//...
mousecursor.grip,./img/curs/hand_grip.cur
//
metainfo,https://raw.githubusercontent.com/Taromati2/Taromati2/master/.ukagaka/
githubrepo,https://github.com/Taromati2/Taromati2
```

A ghost without metainfo can add metainfo and a uuid in this way.  

## uuid

Considering that different versions of the same ghost or different branches of the same ghost may exist, uuid is necessary.  
Web applications can use uuid to distinguish between different ghosts with the same name.  

Given that a UUID may change due to the addition or modification of a metainfo folder address or home URL, a single ghost may have multiple historical UUIDs.  

### UUID Generation

If you're not concerned with the principles of UUID generation, you can use [uuid-genner](https://ukatech.github.io/metainfo-standard/uuid-genner/) to generate a UUID directly. The steps to generate a UUID are as follows:  

1. If the ghost has a metainfo folder, use its URL as the `uuidvalue`.  
  If the ghost does not have a metainfo folder, use its home URL as the `uuidvalue`.  
  If the ghost does not have a home URL, use its name as the `uuidvalue`.  
2. If the ghost has a `uuid_base` field, append its contents to the existing `uuidvalue`.  
3. Encode the `uuidvalue` in `UTF8` without adding newlines at the end, then MD5 encrypt it and base64 encode the resulting binary.  

For instance, the UUID generated from `https://raw.githubusercontent.com/Taromati2/Taromati2/master/.ukagaka/` is `R5dVNluBvKjtQqjP0dAuoA==`.  

### Local Completeness of UUID

A ghost should carry sufficient information to allow an application to compute its UUID without needing a network connection. To this end, the following measures are taken:  

- If the ghost has a metainfo folder, its URL should be recorded in its `descript.txt`.  
- If the ghost's metainfo has a `uuid_base` field, it should be documented in its `descript.txt`.  

### UUID Verification

Web applications should validate the UUID of a new ghost upon capture or receipt to ensure the legitimacy of the information and to prevent confusion between different ghosts. To verify the UUID, the application should:  

- Access the metainfo folder and check for a `jump_to.txt` file.  
- If such a file exists, the application needs to update the URL of this ghost's metainfo folder and its UUID.  

Given that a UUID may change due to changes in the metainfo folder address, a single ghost may have multiple historical UUIDs. Applications should not use the UUID to differentiate between ghosts when building ghost-related requests and logic. Instead, they should include the URL of the metainfo folder so that UUID verification can be based on the most recent information. Applications are allowed to cache past UUIDs of the ghost for quick matching, but should update the cache if the match fails. If the match fails, the application should reject the host registration.  

**Important:** A ghost without a metainfo folder address should not be considered the same as a ghost with a metainfo folder address of the same name, unless it specifies a metainfo folder address via the home URL or metainfo field. For details on appending a UUID to an existing ghost, see [Directing to the metainfo folder via ghost](#directing-to-the-metainfo-folder-via-ghost).  

### Limitations

The UUID only protects hosts with an existing home URL from being obfuscated or overwritten, but does not protect those without a home URL in their history.  
