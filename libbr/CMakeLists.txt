cmake_minimum_required(VERSION 3.1)

aux_source_directory(.              BR_SRC)
aux_source_directory(./assert       BR_SRC_ASSERT)
aux_source_directory(./container    BR_SRC_CONTAINER)
aux_source_directory(./exception    BR_SRC_EXCEPTION)
aux_source_directory(./iterator     BR_SRC_ITERATOR)
aux_source_directory(./math         BR_SRC_MATH)
aux_source_directory(./memory       BR_SRC_MEMORY)
aux_source_directory(./structure    BR_SRC_STRUCTURE)
aux_source_directory(./type_operate BR_SRC_TYPE_OPERATE)
aux_source_directory(./type_traits  BR_SRC_TYPE_TRAITS)
aux_source_directory(./utility      BR_SRC_UTILITY)

add_library (
    br STATIC
    ${BR_SRC}
    ${BR_SRC_ASSERT}
    ${BR_SRC_CONTAINER}
    ${BR_SRC_EXCEPTION}
    ${BR_SRC_ITERATOR}
    ${BR_SRC_MATH}
    ${BR_SRC_MEMORY}
    ${BR_SRC_STRUCTURE}
    ${BR_SRC_TYPE_OPERATE}
    ${BR_SRC_TYPE_TRAITS}
    ${BR_SRC_UTILITY}
)