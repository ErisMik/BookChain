! clang-format src/*.cpp -output-replacements-xml | grep -c '<replacement '
! clang-format src/*.hpp -output-replacements-xml | grep -c '<replacement '
! clang-format src/**/*.cpp -output-replacements-xml | grep -c '<replacement '
! clang-format src/**/*.hpp -output-replacements-xml | grep -c '<replacement '
! clang-format test/*.cpp -output-replacements-xml | grep -c '<replacement '