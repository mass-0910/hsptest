@echo off

@rem ����1�F���̃o�b�`�t�@�C���̓e�X�g�X�N���v�g(test_***.hsp)���܂܂�Ă���t�H���_�ɔz�u���Ă��������B

@rem ����2�F���̃o�b�`�t�@�C����C:\hsp3*�t�H���_��HSP3���C���X�g�[������Ă��邱�Ƃ�z�肵�ď�����Ă���܂��B
@rem C:\hsp3*�ȊO�̏ꏊ��HSP3���C���X�g�[�����Ă���ꍇ�A�ȉ��̕ϐ��ɃC���X�g�[���t�H���_�ւ̃p�X�������Ă��������B
set hsp_dir=

@rem C�h���C�u��������HSP�C���X�g�[���t�H���_��T��
if not defined hsp_dir (
    for /D %%a in (C:\hsp3*) do (
        set hsp_dir=%%a
    )
)

@rem �C���X�g�[���t�H���_���擾�ł��Ȃ�������G���[�\�����ďI��
if not defined hsp_dir (
    echo HSP3�̃C���X�g�[���t�H���_��������܂���ł����B
    echo %0���������Ȃǂ̃G�f�B�^�ŊJ���A7�s�ڂ�hsp_dir�ϐ��ɁA��������PC��HSP3�C���X�g�[���t�H���_�ւ̃p�X����������ł��������B
    echo ��jset hsp_dir=%USERPROFILE%\hsp36
    pause
    exit /B 1
)

@rem hsptest���s
%hsp_dir%\hsptest.exe -v -l hsptest_log.txt -s

pause