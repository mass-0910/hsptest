#ifndef result_format_as_included
#define result_format_as_included

#module

/*
��������stdout�������Ԃ�
�Ԃ�l
    ��������stdout������
*/
#defcfunc get_pass_result_format
    return "&RESULT&{PASS;0;#;#}"

/*
���s����stdout�������Ԃ�
����
    error_line: �G���[�����s��
    error_message: �G���[���b�Z�[�W
�Ԃ�l
    ���s����stdout������
*/
#defcfunc get_fail_result_format int error_line, str error_file, str error_message
    return "&RESULT&{FAIL;" + error_line + ";" + error_file + ";" + error_message + "}"

/*
�R�[���X�^�b�N��stdout�������Ԃ�
����
    file_name: �t�@�C����
    file_line: �t�@�C���s�ԍ�
    depth: �[��
�Ԃ�l
    �R�[���X�^�b�N��stdout������
*/
#defcfunc get_callstack_format str file_name, int file_line, int depth
    return "&CALLSTACK&{" + file_name + ";" + file_line + ";" + depth + "}"

#global

#endif