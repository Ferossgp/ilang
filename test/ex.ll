declare i8* @malloc(i64)

define i32* @array() {
  %1 = alloca i32*, align 8
  %2 = call i8* @malloc(i64 16)
  %3 = bitcast i8* %2 to i32*
  store i32* %3, i32** %1, align 8
  %4 = load i32*, i32** %1, align 8
  ret i32* %4
}
