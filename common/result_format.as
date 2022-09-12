#ifndef result_format_as_included
#define result_format_as_included

#module

/*
成功時のstdout文字列を返す
返り値
    成功時のstdout文字列
*/
#defcfunc get_pass_result_format
    return "&RESULT&{PASS;0;#;#}"

/*
失敗時のstdout文字列を返す
引数
    error_line: エラー発生行数
    error_message: エラーメッセージ
返り値
    失敗時のstdout文字列
*/
#defcfunc get_fail_result_format int error_line, str error_file, str error_message
    return "&RESULT&{FAIL;" + error_line + ";" + error_file + ";" + error_message + "}"

/*
コールスタックのstdout文字列を返す
引数
    file_name: ファイル名
    file_line: ファイル行番号
    depth: 深さ
返り値
    コールスタックのstdout文字列
*/
#defcfunc get_callstack_format str file_name, int file_line, int depth
    return "&CALLSTACK&{" + file_name + ";" + file_line + ";" + depth + "}"

/*
テストカバレッジのstdout文字列を返す
引数
    file_name: ファイル名
    file_line: ファイル行番号
    coverage_type: カバレッジの種類(C0なら0、C1なら1を渡す)
*/
#defcfunc get_coverage_format str file_name, int file_line, int coverage_type, int passed
    if coverage_type == 0 {
        return "&COVERAGE&{" + file_name + ";" + file_line + ";" + coverage_type + ";0}"
    } else {
        return "&COVERAGE&{" + file_name + ";" + file_line + ";" + coverage_type + ";" + passed + "}"
    }

#global

#endif