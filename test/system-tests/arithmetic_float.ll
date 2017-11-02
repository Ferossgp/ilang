define double @add(double %x, double %y) {
entry:
    %tmp = fadd double %x, %y
    ret double %tmp
}

define double @sub(double %x, double %y) {
entry:
    %tmp = fsub double %x, %y
    ret double %tmp
}

define double @mul(double %x, double %y) {
entry:
    %tmp = fmul double %x, %y
    ret double %tmp
}

define double @div(double %x, double %y) {
entry:
    %tmp = fdiv double %x, %y
    ret double %tmp
}

define double @mod(double %x, double %y) {
entry:
    %tmp = frem double %x, %y
    ret double %tmp
}