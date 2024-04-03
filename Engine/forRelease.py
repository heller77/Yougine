# Releaseするときようのスクリプト

import os
import shutil

def copy_files_with_extension(source_dir, dest_dir, extension):
    for root, dirs, files in os.walk(source_dir):
        for file in files:
            if file.endswith(extension):
                source_file_path = os.path.join(root, file)
                relative_path = os.path.relpath(root, source_dir)
                dest_file_path = os.path.join(dest_dir, relative_path, file)

                os.makedirs(os.path.dirname(dest_file_path), exist_ok=True)
                shutil.copy2(source_file_path, dest_file_path)
                print(f"Copied: {source_file_path} to {dest_file_path}")

source_directory = 'Core'  # ここにコピー元のフォルダパスを設定
destination_directory = 'Release/Core'  # ここにコピー先のフォルダパスを設定
extension = '.h'  # コピーしたいファイルの拡張子

copy_files_with_extension(source_directory, destination_directory, extension)


userengincommondirectory="UserEngineCommon/include"
userengincommondirectory_destination="Release/UserEngineCommon/include"
copy_files_with_extension(userengincommondirectory, userengincommondirectory_destination, extension)

# GameBuildをreleaseに配置
gamebuilddirectory="GameBuildProject/"
gamebuilddirectory_disitination="Release/GameBuildProject/"
os.makedirs(os.path.dirname(gamebuilddirectory_disitination), exist_ok=True)
shutil.copy2(gamebuilddirectory+"CMakeLists.txt",gamebuilddirectory_disitination)
shutil.copytree(gamebuilddirectory+"src",gamebuilddirectory_disitination+"src", dirs_exist_ok=True)

#Thir
thirdpartylib="ThirdPartyLibrary/lib"
thirdpartylib_distination="Release/ThirdPartyLibrary/lib"
# copy_files_with_extension(source_directory, destination_directory, extension)
shutil.copytree(thirdpartylib,thirdpartylib_distination, dirs_exist_ok=True)
