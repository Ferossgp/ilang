define i1 @and_op(i1 %x, i1 %y) {
entry:
    %tmp = and i1 %x, %y
    ret i1 %tmp
}

define i1 @or_op(i1 %x, i1 %y) {
entry:
    %tmp = or i1 %x, %y
    ret i1 %tmp
}

define i1 @xor_op(i1 %x, i1 %y) {
entry:
    %tmp = xor i1 %x, %y
    ret i1 %tmp
}

define i1 @not_op(i1 %x) {
entry:
    %tmp = xor i1 %x, true
    ret i1 %tmp 
}