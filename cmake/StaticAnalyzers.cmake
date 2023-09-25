find_program(CLANGTIDY clang-tidy)
set(CMAKE_CXX_CLANG_TIDY 
    ${CLANGTIDY};
    -config-file=../.clang-tidy;
)

find_program(CPPCHECK cppcheck)
set(CMAKE_CXX_CPPCHECK
    ${CPPCHECK}
    --template=gcc
    --enable=style,performance,warning,portability
    --inline-suppr
    --suppress=cppcheckError
    --suppress=internalAstError
    --suppress=unmatchedSupression
    --suppress=passedByValue
    --suppress=syntaxError
    --suppress=preprocessorErrorDirective
    --inconclusive
    --std=c++${CMAKE_CXX_STANDARD}
)
