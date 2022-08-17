#ifndef result_format_as_included
#define result_format_as_included

#module

/*
成功時のstdout文字列を返す
返り値
    成功時のstdout文字列
*/
#defcfunc get_pass_result_format
    return "&RESULT&{PASS,0,#,#}"

/*
失敗時のstdout文字列を返す
引数
    error_line: エラー発生行数
    error_message: エラーメッセージ
返り値
    失敗時のstdout文字列
*/
#defcfunc get_fail_result_format int error_line, str error_file, str error_message
    return "&RESULT&{FAIL," + error_line + "," + error_file + "," + error_message + "}"

/*
stdoutから結果をパースする
引数
    stdout: hspランタイムから出力された文字列
    result: 結果("PASS"または"FAIL")を格納する変数
    error_line: エラーが発生した行数を格納する変数
    error_message: エラーメッセージを格納する変数
    removed_stdout: 特殊フォーマット文字列を全て取り除いた標準出力が格納される変数
*/
#deffunc parse_result_format str stdout, var result, var error_line, var error_file, var error_message, var removed_stdout
    buf = stdout
    notesel buf
    resline = notefind("&RESULT&", 1)
    noteget resultstr, resline
    notedel resline
    notedel resline
    removed_stdout = buf
    resultstr = strmid(resultstr, 9, 1024)
    resultstr = strtrim(resultstr, , '}')
    getstr result, resultstr, 0, ','
    i = strsize
    getstr error_line, resultstr, i, ','
    i += strsize
    getstr error_file, resultstr, i, ','
    i += strsize
    getstr error_message, resultstr, i, ','
    return

#global

#endif