# ukagaka は metainfo 標準を使用します

## metainfoとは？

metainfoは、Webアプリケーションに必要な基本情報を含むukagakaを記述するための拡張可能な標準規格です  

## なぜ metainfo を使うのか？

GCSを例にとると
現在のGCSのバージョンで必要とされる情報アーキテクチャを考えてみましょう。 CGSでゴーストのプレビュー画像をカスタマイズする必要があるとき、ユーザーが使うこともない1つか2つのapngファイルを `shell/matser` に保存する必要があるのです  
これでは、プロジェクトのレイアウトが乱れるだけでなく、用途の異なるファイルが混在することになり、プロジェクトのメンテナンスに支障をきたします  
現在のGCSのバージョンで提供されているリダイレクトは、作者のホームページへのリダイレクトのみで、カスタマイズやカスタマイズに欠けることを考慮してください。  
metainfoは、これらの問題を解決するために作られました。  

## metainfoの構造基準  

### 保管場所  

ローカルのゴーストフォルダーではないクラウドストレージのディレクトリにmetainfoフォルダーを保存しておくと、最新の状態を保つことができ、ユーザーのローカルストレージスペースを占有しないのでおすすめです  
ゴーストがgithub上で別のプロジェクトを持っている場合、プロジェクトのデフォルトブランチのルートにmetainfoフォルダを格納することをお勧めします。  
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

`preview`フォルダにはいくつでもpngファイルを格納できるが、少なくとも2つのpngファイル（それぞれ `sakura.png` と `kero.png` という名前）を格納することを推奨する。  
動的なプレビューを提供したい場合は、`preview` フォルダに `sakura.apng` と `kero.apng` という名前でそれぞれ保存しておくとよいでしょう。  
ゴーストに複数のケロがある場合は、`kero1.png`, `kero2.png`, `kero3.png` などのように名前を追加することが可能です。  

Webアプリケーションの開発者にとっては、`preview`フォルダ全体がオプションであり、その中にあるコンテンツもオプションであることに注意する必要があります。  

##### `descript.txt`

`descript.txt` ファイルの内容は必須であり、`UTF8` でエンコードされ、このフォーマットに従ったものでなければならない。  

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
languages,Simplified Chinese	//,Japanese,Engilsh may be available in future
```

行末までの `://` で始まらない `//` はコメントとして扱われ、解析されません。  
スタートとして `//meta info` が必要です。  
以下のオプションが必要です。  
`type`: 型 (後の標準的な展開のためのもの)、`ghost` でなければならない  
名前`: 名前  
クラフトマン`: プロデューサー  
`craftmanurl`: 制作者へのリンクです。  
`uuid`: 一意な識別子、詳しくは [UUID規格](#uuid) を参照。  
`languages`: ghost がサポートする自然言語。複数ある場合は `,` で区切る。  
`type` が `ghost` である場合、以下のオプションが必要である。  
`sakura.name`: イネーブラの名前 `0`.  
ghostが必ずしもサーバントを持つとは限らないことを考慮して、`kero.name`はオプション（必須ではありません）です。  
`kero.name`: メイド `kero1` の名前 (複数のメイドがいる場合は `kero1.name`, `kero2.name` 等で区別できる)  

必須ではありません。
`has_terms`: 項目があるかどうか (ない場合は 0、ある場合は 1、書かれていない場合はデフォルト 0)  
`icon`: アイコンのリンク (未執筆の場合、デフォルトは metainfo フォルダにある `icon.png` (ファイルが存在する場合))  
`uuid_base`: uuidの衝突を防ぐためのuuidベース (詳細は [UUID標準](#uuid) を参照)  

##### リンク

links`フォルダには、関連するリンク情報を保持するために、好きなだけtxtファイルを保存することができます。標準では、以下のファイルが指定されています（ただし、必須ではありません）。

- `mirror_repo.txt`: ゴーストファイルの内容がこのリポジトリで更新されない場合、このファイルにミラーリポジトリへのリンクを書くことができます。 
  リンクは github リポジトリのリンクである必要があります。  
- `nar_release_repo.txt`: あなたのゴーストのnarファイルがこのリポジトリでリリースされていない場合、このファイルにあなたのnarリリースリポジトリへのリンクを記述することができます。  
  リンクは github リポジトリのリンクである必要があります。

それ以外のファイルは、標準的な拡張子はサードパーティに任せ、標準仕様のファイルを新たに追加する可能性は、後から排除することができる。  
一般的ではない推奨のサードパーティ製拡張機能は、ファイル名にウェブアプリケーション名またはその略称を含める必要があります（例：`GCS_link.txt`）。

##### `infos`

infos`フォルダには、Webアプリケーションの関連情報を格納するために必要な数のtxtファイルを格納することができます。 

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

## uuid

同じゴーストの異なるバージョンや、同じゴーストの異なるブランチが存在する可能性を考慮し、uuidは必要である  
ウェブアプリケーションは、uuidを使用して、同じ名前の実質的に異なるバージョンを区別することができます。  

### uuidの生成  

uuidを生成するには、現在のゴーストのmetainfoフォルダのURLを取得し（`UTF8`でエンコードし、最後に改行しない）、それをmd5で暗号化し、バイナリ結果をbase64でエンコードする必要があります。  
例えば、`https://raw.githubusercontent.com/Taromati2/Taromati2/master/.ukagaka/` が生成する uuid は `R5dVNluBvKjtQqjP0dAuoA==` です。  
ghostにmetainfoフォルダがない場合、uuidはbase64エンコードされ、バイナリ結果は`0`となる。  
metainfoに `uuid_base` フィールドがある場合は、前のステップで取得したuuidの前に直接追加してください。  
uuid_base` フィールドは uuid を不定にするが、アプリケーションが 64 ビットより長い uuid を拒否することを可能にする  

### uuidチェックサム  

Webアプリケーションは、新しいゴーストをキャプチャまたは受信したときに、情報の正当性を確認するために、異なるゴーストを混同する可能性を避けるために、そのuuidを検証する必要があります。 
uuidチェックは、metainfoフォルダにアクセスして、`jump_to.txt`ファイルがあるかどうかをチェックする必要があります。  
uuidはmetainfoフォルダのアドレスの変更によって変わる可能性があるため、アプリケーション間のゴースト特定リクエストではuuidを使用してゴーストを区別せず、uuidチェックサムが最新の情報に基づくように、metainfoフォルダのURLを含める必要があります。  
アプリケーションは、ゴーストの高速マッチングのために過去のuuidをキャッシュすることができますが、マッチングに失敗した場合はキャッシュを更新する必要があります。  
チェックサムが失敗した場合、アプリケーションはこのゴーストに関連する登録を拒否する必要があります。  

### デメリット

uuidは、uuidを持つ既存のゴーストを混乱や置き換えから守ることができるだけで、履歴にuuidがないゴーストを混乱から守ることはできません。  
