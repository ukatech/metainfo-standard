- [CN](./README_CN.md)  
- [EN](./README_EN.md)  
- [JP](./README_JP.md)  

________

# 伺かで metainfo 標準を使いましょう

## metainfoとは？

metainfoは、Webアプリケーションに必要な基本情報を含む伺かを表現するための拡張可能な標準規格です。  

## なぜ metainfo を使うのか？

[ゴーストキャプターさくら](http://buynowforsale.shillest.net/ghosts/)(GCS)を例にしましょう。
現在のGCSのバージョンで必要とされる情報アーキテクチャを考えてみましょう。 GCSでゴーストのプレビュー画像をカスタマイズする必要があるとき、ユーザーが使うこともない1つか2つのapngファイルを `shell/master` に保存する必要があるのです。  
これでは、プロジェクトのレイアウトが乱れるだけでなく、用途の異なるファイルが混在することになり、プロジェクトのメンテナンスに支障をきたします。  
現在のGCSのバージョンで提供されているリダイレクトは、作者のホームページへのリダイレクトのみで、カスタマイズに欠けることを考慮してください。  
metainfoは、これらの問題を解決するために作られました。  

## metainfoの構造基準  

### 保管場所  

ローカルのゴーストフォルダーではないクラウドストレージのディレクトリにmetainfoフォルダーを保存しておくと、最新の状態を保つことができ、ユーザーのローカルストレージスペースを占有しないのでおすすめです。  
ゴーストがgithub上で別のプロジェクトを持っている場合、プロジェクトのデフォルトブランチのルートにmetainfoフォルダを格納することを推奨します。  
例えば `https://github.com/Taromati2/Taromati2` の場合、標準では、metainfo フォルダは `https://github.com/Taromati2/Taromati2/tree/master/.ukagaka` に格納されます (ここで `master` はデフォルトのブランチです)  

### 関連タグ  

もし、あなたのゴーストがgithub上の別のプロジェクトとmetainfoフォルダを持っているなら、いくつかのウェブアプリケーションがあなたのゴーストを認識できるように、プロジェクトに `ukagaka-ghost` タグを追加することをお勧めします。  

### ファイル構成  

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

または

```filetree
/.ukagaka
    └── jump_to.txt
```

#### ファイルの説明  

- `descript.txt`: ゴーストの説明ファイル、ウェブアプリケーションの基本情報を提供するために使用されます。 
- `preview`: ゴーストのプレビューフォルダで、ウェブアプリケーションでプレビュー画像を提供するために使用されます (必須ではありません)  
- `icon.png`: ゴーストのアイコンファイルで、ウェブアプリケーションでアイコンを提供するために使用されます (必須ではありません)  
- `links`: ゴーストのリンクフォルダ。ウェブアプリケーションで拡張可能で関連性の高いリンク情報を提供するために使用されます（必須ではありません）。
- `infos`: ゴーストの情報フォルダ。ウェブアプリケーションで拡張可能な追加情報を提供するために使用されます (必須ではありません)
- `jump_to.txt`: 新しいメタ情報フォルダにリダイレクトするためのメタ情報フォルダジャンプファイル（現在のフォルダが非推奨の場合にのみ使用されます。）  

#### 内容の紹介

##### `preview`

`preview`フォルダにはいくつでもpngファイルを格納できますが、少なくとも2つのpngファイル（それぞれ `sakura.png` と `kero.png` という名前）を格納することを推奨します。  
動的なプレビューを提供したい場合は、`preview` フォルダに `sakura.apng` と `kero.apng` という名前でそれぞれ保存しておくとよいでしょう。  
ゴーストに複数の相方がいる場合は、`kero1.png`, `kero2.png`, `kero3.png` などのように名前を追加することが可能です。  

Webアプリケーションの開発者にとっては、`preview`フォルダ全体がオプションであり、その中にあるコンテンツもオプションであることに注意する必要があります。  

##### `descript.txt`

`descript.txt` ファイルの内容は必須であり、`UTF8` でエンコードされ、このフォーマットに従ったものでなければならなりません。  

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

行末までの `://` で始まらない `//` はコメントとして扱われ、解析されません。  
スタートとして `//meta info` が必要です。  
以下のオプションが必要です。  
`type`: 型 (後の標準的な展開のためのもの)、`ghost` でなければならない  
`name`: 名前  
`craftman`: 製作者  
`craftmanurl`: 制作者へのリンク  
`uuid`: 一意な識別子、詳しくは [UUID規格](#uuid) を参照  
`languages`: ghost がサポートする言語。複数ある場合は `,` で区切る。  
`type` が `ghost` である場合、以下のオプションが必要である。  
`sakura.name`: メインキャラの名前  
ghostが必ずしもサーバントを持つとは限らないことを考慮して、`kero.name`はオプション（必須ではありません）です。  
`kero.name`: 相方 `kero1` の名前 (複数の相方がいる場合は `kero1.name`, `kero2.name` 等で区別できる)  

オプション項目  
`has_terms`: 項目([`terms.txt`](https://ssp.shillest.net/ukadoc/manual/manual_directory.html))があるかどうか (ない場合は 0、ある場合は 1、書かれていない場合はデフォルト 0)  
`icon`: アイコンのリンク (未記載の場合、デフォルトは metainfo フォルダにある `icon.png` (ファイルが存在する場合))  
`uuid_base`: uuidの衝突を防ぐためのuuidベース (詳細は [UUID標準](#uuid) を参照)  

##### リンク

`links`フォルダには、関連するリンク情報を保持するために、好きなだけtxtファイルを保存することができます。標準では、以下のファイルが指定されています（ただし、必須ではありません）。

- `mirror_repo.txt`: ゴーストファイルの内容がこのリポジトリで更新されない場合、このファイルにミラーリポジトリへのリンクを書くことができます。 
  リンクは github リポジトリのリンクである必要があります。  
- `nar_release_repo.txt`: あなたのゴーストのnarファイルがこのリポジトリでリリースされていない場合、このファイルにあなたのnarリリースリポジトリへのリンクを記述することができます。  
  リンクは github リポジトリのリンクである必要があります。

上記のファイルの内容は、次のように複数の空白行末を持つ単一のURLにすることができます。  

**nar_release_repo.txt**

```txt
https://github.com/Taromati2/package-factory


```

また、より多くの情報やオプションのコメントを含む複雑なものにすることもできる。  
この場合、上記のファイルの内容は `UTF8` エンコードされるべきであり、行末までの `://` で始まらない `//` はコメントとみなされ、解析されるべきではありません。  

**nar_release_repo.txt**

```txt
//a info file to tell the web app where to find the nar release repo
link, https://github.com/Taromati2/package-factory
nar_file_name, Taromati2.nar  //the nar file name

```

この場合、`link` フィールドは必須で、他のフィールドはオプションです。  
`nar_file_name` フィールドは `nar_release_repo.txt` で使用され、ゴーストの nar ファイルとみなすべきリポのリリースの nar ファイルをウェブアプリケーションに伝えます。  

それ以外のファイルは、標準的な拡張子はサードパーティに任せ、標準仕様のファイルを新たに追加する可能性は、後から排除することができます。  
一般的ではない推奨のサードパーティ製拡張機能は、ファイル名にウェブアプリケーション名またはその略称を含めるべきです（例：`GCS_link.txt`）。

##### `infos`

`infos`フォルダには、Webアプリケーションの関連情報を格納するために必要な数のtxtファイルを格納することができます。 

## ghost経由でmetainfoフォルダに誘導する  

Ghostの開発者は、`ghost/descript.txt`に `metainfo` フィールドを書き、その後にmetainfoフォルダのURLを書いて、特定のアプリケーションをghost経由でmetainfoフォルダに誘導できるようにすることが推奨されます。
また、`ghost/descript.txt` に `githubrepo` フィールドを記述し、その後に github プロジェクトの url を記述しても、同じ効果を持ち、同時に存在することができます。  
例

```txt
//...
mousecursor.grip,./img/curs/hand_grip.cur
//
metainfo,https://raw.githubusercontent.com/Taromati2/Taromati2/master/.ukagaka/
githubrepo,https://github.com/Taromati2/Taromati2
```

metainfoを持たないゴーストは、このようにmetainfoとuuidを付加することができます。  

## uuid

同じゴーストの異なるバージョンや、同じゴーストの異なるブランチが存在する可能性を考慮し、uuidは必要です。  
ウェブアプリケーションは、uuidを使用して、同じ名前の実質的に異なるバージョンを区別することができます。  

UUIDは、metainfoフォルダのアドレスやhomeurlの追加や変更により変化する可能性があるため、同一のゴーストが複数の過去のUUIDを持つ可能性があります。  

### UUIDの生成

UUIDの生成原理については気にしない場合、[uuid-genner](https://github.com/ukatech/metainfo-standard/tree/master/uuid-genner)を使用してUUIDを直接生成することができます。  
UUIDの生成方法は以下の通りです：  

1. ゴーストがmetainfoフォルダを持っている場合、そのURLを`uuidvalue`として使用します。
  ゴーストがmetainfoフォルダを持っていない場合、そのhomeurlを`uuidvalue`として使用します。
  ゴーストがhomeurlを持っていない場合、その名前を`uuidvalue`として使用します。
2. ゴーストが`uuid_base`フィールドを持っている場合、その内容を既存の`uuidvalue`に追加します。
3. `uuidvalue`を`UTF8`でエンコードし、改行を追加せずにMD5で暗号化し、その結果をbase64でエンコードします。

例えば、`https://raw.githubusercontent.com/Taromati2/Taromati2/master/.ukagaka/`から生成されるUUIDは`R5dVNluBvKjtQqjP0dAuoA==`です。  

### UUIDのローカル完全性

ゴーストは、アプリケーションがネットワーク接続なしでUUIDを計算できるように、十分な情報を持つべきです。  
そのために、以下の措置を講じます：  
ゴーストがmetainfoフォルダを持っている場合、そのURLを`descript.txt`に記録します。  
ゴーストのmetainfoに`uuid_base`フィールドがある場合、それを`descript.txt`に記録します。  

### UUIDの検証

新しいゴーストをキャプチャまたは受信したときに、そのゴーストのUUIDを検証し、情報の正当性を確認し、異なるゴーストを混同することを防ぐべきです。  
UUIDの検証は、metainfoフォルダにアクセスし、`jump_to.txt`ファイルが存在するかどうかを確認することで行います。  
metainfoフォルダのアドレスが変更されるとUUIDが変更される可能性があるため、同一のゴーストが複数の過去のUUIDを持つ可能性があります。  
アプリケーションは、ゴースト関連のリクエストやロジックを構築する際に、UUIDを使用してゴーストを区別するべきではありません。代わりに、metainfoフォルダのURLを含めて、UUIDの検証が最新の情報に基づいて行われるようにすべきです。  
アプリケーションは、ゴーストの過去のUUIDをキャッシュして高速にマッチングを行うことが許可されていますが、マッチングが失敗した場合はキャッシュを更新すべきです。  
マッチングが失敗した場合、アプリケーションはそのホストの登録を拒否すべきです。  

**重要：** metainfoフォルダのアドレスを持たないゴーストは、homeurlまたはmetainfoフィールドでmetainfoフォルダのアドレスを指定するまで、同じ名前のmetainfoフォルダのアドレスを持つゴーストと同一のゴーストとして定義すべきではありません。  
既存のゴーストにUUIDを追加する方法については、[ghost経由でmetainfoフォルダに誘導する](#ghost経由でmetainfoフォルダに誘導する)を参照してください。  

### 制限事項

UUIDは、既存のhomeurlを持つホストを混乱や上書きから保護しますが、その履歴にhomeurlがないホストを上書きから保護することはできません。  
