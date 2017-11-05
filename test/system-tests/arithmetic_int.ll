define i32 @add(i32 %x, i32 %y) {
entry:
    %tmp = add i32 %x, %y
    ret i32 %tmp
}

define i32 @sub(i32 %x, i32 %y) {
entry:
    %tmp = sub i32 %x, %y
    ret i32 %tmp
}

define i32 @mul(i32 %x, i32 %y) {
entry:
    %tmp = mul i32 %x, %y
    ret i32 %tmp
}

define i32 @div(i32 %x, i32 %y) {
entry:
    %tmp = sdiv i32 %x, %y
    ret i32 %tmp
}

define i32 @mod(i32 %x, i32 %y) {
entry:
    %tmp = srem i32 %x, %y
    ret i32 %tmp
}
