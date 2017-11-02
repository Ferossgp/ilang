define i32 @neg_i(i32 %x) {
entry:
    %tmp = sub i32 0, %x
    ret i32 %tmp
}

define double @neg_f(double %x) {
entry:
    %tmp = fsub double 0.0, %x
    ret double %tmp
}


