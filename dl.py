import zipfile
import requests
import os
 
ZIP_URL = "https://dxlib.xsrv.jp/DxLib/DxLib_VC3_24b.zip"
 
 
# 指定URL（第1引数）からファイルを取得して、指定パス（第2引数）に保存する
def file_download(url):
    """URL を指定してカレントディレクトリにファイルをダウンロードする
    """
    filename = url.split('/')[-1]
    r = requests.get(url, stream=True)
    with open(filename, 'wb') as f:
        for chunk in r.iter_content(chunk_size=1024):
            if chunk:
                f.write(chunk)
                f.flush()
        return filename

    # ファイルが開けなかった場合は False を返す
    return False
 
def zip_extract(filename):
    """ファイル名を指定して zip ファイルをカレントディレクトリに展開する
    """
    target_directory = '.'
    zfile = zipfile.ZipFile(filename)
    for info in zfile.infolist():
        info.filename = info.orig_filename.encode('cp437').decode('cp932')
        if os.sep != "/" and os.sep in info.filename:
            info.filename = info.filename.replace(os.sep, "/")
        zfile.extract(info)
    """zfile.extractall(target_directory)"""


if __name__ == "__main__":
    filename = file_download(ZIP_URL)
    if filename:
        zip_extract(filename)
    else:
         print('Failed')
    input()