@echo off

@rem HSP�C���X�g�[���t�H���_���擾����
if "%1"=="" (
    for /D %%a in (C:\hsp3*) do (
        set hsp_dir=%%a
    )
) else (
    if not exist "%1" (
        echo %1 �F�t�H���_��������܂���
        pause
        exit /B 1
    )
    set hsp_dir=%1
)

@rem �C���X�g�[���t�H���_���擾�ł��Ȃ�������G���[�\�����ďI��
if not defined hsp_dir (
    echo HSP3�̃C���X�g�[���t�H���_��������܂���ł����B
    echo ���̃o�b�`�t�@�C���̈�����HSP3�̃C���X�g�[���t�H���_�̃p�X����͂��Ă��������B
    echo ��j> install.bat C:\hsp36
    pause
    exit /B 1
)

@rem hsptest�̃C���X�g�[�����J�n����
echo %hsp_dir%��hsptest�̃C���X�g�[�����J�n���܂��B
copy /Y hsptest.exe %hsp_dir%
copy /Y common\* %hsp_dir%\common

if %ERRORLEVEL% neq 0 (
    echo hsptest�̃C���X�g�[���Ɏ��s���܂����B
    pause
    exit /B 1
)

echo hsptest�̃C���X�g�[�����������܂����B
pause