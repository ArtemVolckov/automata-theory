/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "parser.y"

#include "../ast/ast.hpp"

Ast ast;

struct Value {
    int int_val;
    std::string str_val;
    // pair.fist = variable name; pair.second = variable.value
    std::vector<std::pair<std::variant<std::string, char>, std::variant<int, bool, std::string, char>>> variables;
    bool is_elipsis, is_int_val, is_bool_val, is_str_val, is_variable, is_vector;
    std::pair<std::variant<int, bool, std::string>, std::variant<int, bool, std::string, char>> logical_op_variables;
    std::string logical_op;
    Node* new_node;
    std::vector<Node*> statements;
    std::vector<std::vector<Node*>> statements_list;
};

#define YYSTYPE Value

int yylex();
void yyerror(std::string err_msg);

#line 95 "parser.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_INTEGER_LITERAL = 3,            /* INTEGER_LITERAL  */
  YYSYMBOL_STRING_LITERAL = 4,             /* STRING_LITERAL  */
  YYSYMBOL_BOOL_LITERAL = 5,               /* BOOL_LITERAL  */
  YYSYMBOL_NAME = 6,                       /* NAME  */
  YYSYMBOL_ASSIGN = 7,                     /* ASSIGN  */
  YYSYMBOL_TO = 8,                         /* TO  */
  YYSYMBOL_ELIPSIS = 9,                    /* ELIPSIS  */
  YYSYMBOL_TYPE = 10,                      /* TYPE  */
  YYSYMBOL_ARITHMETIC_OP = 11,             /* ARITHMETIC_OP  */
  YYSYMBOL_LOGICAL_OP = 12,                /* LOGICAL_OP  */
  YYSYMBOL_VECTOR = 13,                    /* VECTOR  */
  YYSYMBOL_PUSH_POP_FRONT_BACK = 14,       /* PUSH_POP_FRONT_BACK  */
  YYSYMBOL_DO = 15,                        /* DO  */
  YYSYMBOL_UNTIL = 16,                     /* UNTIL  */
  YYSYMBOL_IF = 17,                        /* IF  */
  YYSYMBOL_THEN = 18,                      /* THEN  */
  YYSYMBOL_ELSE = 19,                      /* ELSE  */
  YYSYMBOL_FUNCTION = 20,                  /* FUNCTION  */
  YYSYMBOL_RETURN = 21,                    /* RETURN  */
  YYSYMBOL_22_ = 22,                       /* '='  */
  YYSYMBOL_23_ = 23,                       /* '('  */
  YYSYMBOL_24_ = 24,                       /* ')'  */
  YYSYMBOL_25_ = 25,                       /* '['  */
  YYSYMBOL_26_ = 26,                       /* ']'  */
  YYSYMBOL_27_n_ = 27,                     /* '\n'  */
  YYSYMBOL_28_ = 28,                       /* ','  */
  YYSYMBOL_YYACCEPT = 29,                  /* $accept  */
  YYSYMBOL_program = 30,                   /* program  */
  YYSYMBOL_function_declarations = 31,     /* function_declarations  */
  YYSYMBOL_function_declaration = 32,      /* function_declaration  */
  YYSYMBOL_parameter_list = 33,            /* parameter_list  */
  YYSYMBOL_parameter = 34,                 /* parameter  */
  YYSYMBOL_statements = 35,                /* statements  */
  YYSYMBOL_statement = 36,                 /* statement  */
  YYSYMBOL_func_call_parameter_list = 37,  /* func_call_parameter_list  */
  YYSYMBOL_func_call_parameter = 38,       /* func_call_parameter  */
  YYSYMBOL_else_list = 39,                 /* else_list  */
  YYSYMBOL_variables_list = 40,            /* variables_list  */
  YYSYMBOL_variable = 41,                  /* variable  */
  YYSYMBOL_vector_variables_list = 42,     /* vector_variables_list  */
  YYSYMBOL_vector_variable = 43,           /* vector_variable  */
  YYSYMBOL_bool_expression = 44,           /* bool_expression  */
  YYSYMBOL_expression = 45,                /* expression  */
  YYSYMBOL_46_1 = 46                       /* @1  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  7
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   116

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  29
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  18
/* YYNRULES -- Number of rules.  */
#define YYNRULES  60
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  108

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   276


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      27,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      23,    24,     2,     2,    28,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    22,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    25,     2,    26,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    40,    40,    41,    45,    46,    49,    52,    55,    61,
      67,    72,    77,    80,    84,    87,    94,    97,   103,   107,
     113,   116,   119,   122,   125,   128,   131,   134,   137,   140,
     146,   151,   154,   158,   161,   168,   171,   174,   181,   187,
     193,   196,   202,   207,   213,   216,   223,   226,   232,   237,
     243,   249,   256,   281,   308,   309,   309,   360,   364,   368,
     372
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "INTEGER_LITERAL",
  "STRING_LITERAL", "BOOL_LITERAL", "NAME", "ASSIGN", "TO", "ELIPSIS",
  "TYPE", "ARITHMETIC_OP", "LOGICAL_OP", "VECTOR", "PUSH_POP_FRONT_BACK",
  "DO", "UNTIL", "IF", "THEN", "ELSE", "FUNCTION", "RETURN", "'='", "'('",
  "')'", "'['", "']'", "'\\n'", "','", "$accept", "program",
  "function_declarations", "function_declaration", "parameter_list",
  "parameter", "statements", "statement", "func_call_parameter_list",
  "func_call_parameter", "else_list", "variables_list", "variable",
  "vector_variables_list", "vector_variable", "bool_expression",
  "expression", "@1", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-30)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-52)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
       1,    17,   -30,    36,    18,   -11,    40,   -30,    22,   -30,
      32,   -30,    53,    39,     6,   -30,    62,    42,     9,   -30,
     -30,   -30,    47,   -30,   -30,    -3,    57,    61,    47,    73,
      77,    47,   -30,    77,    29,    77,    81,    66,    67,   -30,
      92,    16,   -30,   -30,    -8,   -30,    82,     2,   -30,   -10,
     -30,    -4,    72,    74,    -2,   -30,   -30,   -30,    80,    23,
     -30,    85,   -30,    57,   -30,    69,   -30,    73,    47,    77,
      77,    77,   -30,   -30,   -30,   -30,   -30,    88,    76,    81,
     -30,   -30,   -30,   -30,   -30,    92,    78,    35,    93,    93,
      93,   -30,   -30,   -30,   -30,   -30,   -30,   -30,    47,    87,
     101,    47,    47,    83,    47,   106,    84,   -30
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       2,     0,     4,     0,     3,     8,     0,     1,     6,     7,
       0,     5,    13,    17,     0,    12,     0,     0,     0,    14,
      16,    15,     0,    10,    11,     0,     0,     0,     0,    54,
      54,     9,    19,    54,     0,    54,    32,    47,     0,    43,
       0,     0,    57,    59,    58,    60,     0,     0,    58,     0,
      18,     0,     0,     0,     0,    36,    38,    37,     0,     0,
      31,     0,    20,     0,    50,     0,    49,    54,     0,    54,
      54,    54,    29,    22,    25,    24,    23,     0,     0,     0,
      44,    46,    45,    42,    21,     0,     0,    41,    55,    52,
      53,    33,    35,    34,    28,    30,    48,    27,     0,    26,
       0,    40,     0,     0,    39,     0,     0,    56
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -30,   -30,   -30,   107,   -30,    94,   -28,   -29,   -30,    34,
     -30,   -30,    51,   -30,    30,    49,   -27,   -30
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     3,     4,     5,    14,    15,    31,    32,    59,    60,
      99,    38,    39,    65,    66,    46,    47,   100
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      41,    69,    50,    49,    33,    34,    51,    69,    54,    69,
     -51,    35,    50,    69,    70,    13,     9,    72,    23,   -51,
      36,     1,    25,    73,    71,    76,    26,     6,     2,    27,
      17,    28,    67,    29,    18,    52,     7,    30,     1,    53,
      87,    25,    88,    89,    90,    26,    10,    78,    27,    11,
      28,    79,    29,    25,    98,    12,    30,    26,    50,    13,
      27,    16,    28,    37,    29,    19,    20,    21,    30,    22,
     101,    40,    50,    61,   104,    50,    42,    43,    44,    45,
      42,    43,    48,    45,    55,    56,    57,    58,    80,    81,
      82,    91,    92,    93,    62,    63,    84,    85,    64,    74,
      68,    75,    77,    94,    69,    97,   102,   103,   105,   106,
     107,     8,    24,    95,    83,    96,    86
};

static const yytype_int8 yycheck[] =
{
      28,    11,    31,    30,     7,     8,    33,    11,    35,    11,
      18,    14,    41,    11,    12,     6,    27,    27,     9,    27,
      23,    20,     6,    27,    22,    27,    10,    10,    27,    13,
      24,    15,    16,    17,    28,     6,     0,    21,    20,    10,
      68,     6,    69,    70,    71,    10,     6,    24,    13,    27,
      15,    28,    17,     6,    19,    23,    21,    10,    87,     6,
      13,    22,    15,     6,    17,     3,     4,     5,    21,    27,
      98,    10,   101,     7,   102,   104,     3,     4,     5,     6,
       3,     4,     5,     6,     3,     4,     5,     6,     3,     4,
       5,     3,     4,     5,    27,    28,    27,    28,     6,    27,
      18,    27,    22,    27,    11,    27,    19,     6,    25,     3,
      26,     4,    18,    79,    63,    85,    67
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    20,    27,    30,    31,    32,    10,     0,    32,    27,
       6,    27,    23,     6,    33,    34,    22,    24,    28,     3,
       4,     5,    27,     9,    34,     6,    10,    13,    15,    17,
      21,    35,    36,     7,     8,    14,    23,     6,    40,    41,
      10,    35,     3,     4,     5,     6,    44,    45,     5,    45,
      36,    45,     6,    10,    45,     3,     4,     5,     6,    37,
      38,     7,    27,    28,     6,    42,    43,    16,    18,    11,
      12,    22,    27,    27,    27,    27,    27,    22,    24,    28,
       3,     4,     5,    41,    27,    28,    44,    35,    45,    45,
      45,     3,     4,     5,    27,    38,    43,    27,    19,    39,
      46,    35,    19,     6,    35,    25,     3,    26
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    29,    30,    30,    31,    31,    31,    31,    31,    32,
      33,    33,    33,    33,    34,    34,    34,    34,    35,    35,
      36,    36,    36,    36,    36,    36,    36,    36,    36,    36,
      37,    37,    37,    38,    38,    38,    38,    38,    38,    39,
      39,    39,    40,    40,    41,    41,    41,    41,    42,    42,
      43,    44,    44,    44,    45,    46,    45,    45,    45,    45,
      45
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     1,     1,     3,     2,     2,     1,     8,
       3,     3,     1,     0,     3,     3,     3,     1,     2,     1,
       3,     4,     4,     4,     4,     4,     5,     5,     5,     3,
       3,     1,     0,     3,     3,     3,     1,     1,     1,     3,
       2,     0,     3,     1,     3,     3,     3,     1,     3,     1,
       1,     1,     3,     3,     0,     0,     8,     1,     1,     1,
       1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 5: /* function_declarations: function_declarations function_declaration '\n'  */
#line 46 "parser.y"
                                                      {
        ast.functions.push_back(yyvsp[-1].new_node);
    }
#line 1198 "parser.tab.c"
    break;

  case 6: /* function_declarations: function_declarations function_declaration  */
#line 49 "parser.y"
                                                 {
        ast.functions.push_back(yyvsp[0].new_node);
    }
#line 1206 "parser.tab.c"
    break;

  case 7: /* function_declarations: function_declaration '\n'  */
#line 52 "parser.y"
                                {
        ast.functions.push_back(yyvsp[-1].new_node);
    }
#line 1214 "parser.tab.c"
    break;

  case 8: /* function_declarations: function_declaration  */
#line 55 "parser.y"
                           {
        ast.functions.push_back(yyvsp[0].new_node);
    }
#line 1222 "parser.tab.c"
    break;

  case 9: /* function_declaration: FUNCTION TYPE NAME '(' parameter_list ')' '\n' statements  */
#line 61 "parser.y"
                                                              {
        yyval.new_node = new Node(NodeType::FUNCTION_DECLARATION, yyvsp[-6].str_val, yyvsp[-5].str_val, yyvsp[-3].variables, yyvsp[0].statements, yyvsp[-3].is_elipsis);
    }
#line 1230 "parser.tab.c"
    break;

  case 10: /* parameter_list: parameter_list ',' ELIPSIS  */
#line 67 "parser.y"
                               {
        for (auto pair: yyvsp[-2].variables)
            yyval.variables.push_back(pair);
        yyval.is_elipsis = true;
    }
#line 1240 "parser.tab.c"
    break;

  case 11: /* parameter_list: parameter_list ',' parameter  */
#line 72 "parser.y"
                                   {
        for (auto pair: yyvsp[-2].variables)
            yyval.variables.push_back(pair);
        yyval.variables.push_back(yyvsp[0].variables.back());
    }
#line 1250 "parser.tab.c"
    break;

  case 12: /* parameter_list: parameter  */
#line 77 "parser.y"
                {
        yyval.variables.push_back(yyvsp[0].variables.back());   
    }
#line 1258 "parser.tab.c"
    break;

  case 14: /* parameter: NAME '=' INTEGER_LITERAL  */
#line 84 "parser.y"
                             {
        yyval.variables.push_back(std::make_pair(yyvsp[-2].str_val, yyvsp[0].int_val));
    }
#line 1266 "parser.tab.c"
    break;

  case 15: /* parameter: NAME '=' BOOL_LITERAL  */
#line 87 "parser.y"
                            {
        bool bool_val = false;

        if (yyvsp[0].str_val == "true")
            bool_val = true;    
        yyval.variables.push_back(std::make_pair(yyvsp[-2].str_val, bool_val));
    }
#line 1278 "parser.tab.c"
    break;

  case 16: /* parameter: NAME '=' STRING_LITERAL  */
#line 94 "parser.y"
                              {
        yyval.variables.push_back(std::make_pair(yyvsp[-2].str_val, yyvsp[0].str_val));
    }
#line 1286 "parser.tab.c"
    break;

  case 17: /* parameter: NAME  */
#line 97 "parser.y"
           {
        yyval.variables.push_back(std::make_pair(yyvsp[0].str_val, '\0'));
    }
#line 1294 "parser.tab.c"
    break;

  case 18: /* statements: statements statement  */
#line 103 "parser.y"
                         {
        yyval.statements = std::move(yyvsp[-1].statements);
        yyval.statements.push_back(yyvsp[0].new_node);    
    }
#line 1303 "parser.tab.c"
    break;

  case 19: /* statements: statement  */
#line 107 "parser.y"
                {
        yyval.statements.push_back(yyvsp[0].new_node);
    }
#line 1311 "parser.tab.c"
    break;

  case 20: /* statement: TYPE variables_list '\n'  */
#line 113 "parser.y"
                             {
        yyval.new_node = new Node(NodeType::VARIABLES_INIT, yyvsp[-2].str_val, yyvsp[-1].variables);
    }
#line 1319 "parser.tab.c"
    break;

  case 21: /* statement: VECTOR TYPE vector_variables_list '\n'  */
#line 116 "parser.y"
                                             {
        yyval.new_node = new Node(yyvsp[-2].str_val, yyvsp[-1].variables, NodeType::VECTOR_INIT);
    }
#line 1327 "parser.tab.c"
    break;

  case 22: /* statement: NAME ASSIGN expression '\n'  */
#line 119 "parser.y"
                                  {
        yyval.new_node = new Node(NodeType::ASSIGN, yyvsp[-3].str_val, yyvsp[-1].is_int_val, yyvsp[-1].is_bool_val, yyvsp[-1].is_str_val, yyvsp[-1].is_variable, yyvsp[-1].is_vector, yyvsp[-1].int_val, yyvsp[-1].str_val);
    }
#line 1335 "parser.tab.c"
    break;

  case 23: /* statement: NAME PUSH_POP_FRONT_BACK expression '\n'  */
#line 122 "parser.y"
                                               {
        yyval.new_node = new Node(NodeType::PUSH_POP_FRONT_BACK, yyvsp[-3].str_val, yyvsp[-2].str_val, yyvsp[-1].is_int_val, yyvsp[-1].is_bool_val, yyvsp[-1].is_str_val, yyvsp[-1].is_variable, yyvsp[-1].is_vector, yyvsp[-1].int_val, yyvsp[-1].str_val);
    }
#line 1343 "parser.tab.c"
    break;

  case 24: /* statement: NAME TO TYPE '\n'  */
#line 125 "parser.y"
                        {
        yyval.new_node = new Node(yyvsp[-3].str_val, NodeType::NAME_TO_TYPE, yyvsp[-1].str_val);
    }
#line 1351 "parser.tab.c"
    break;

  case 25: /* statement: NAME TO NAME '\n'  */
#line 128 "parser.y"
                        {
        yyval.new_node = new Node(NodeType::NAME_TO_NAME, yyvsp[-3].str_val, yyvsp[-1].str_val);
    }
#line 1359 "parser.tab.c"
    break;

  case 26: /* statement: IF bool_expression THEN statements else_list  */
#line 131 "parser.y"
                                                   {
        yyval.new_node = new Node(NodeType::IF, yyvsp[-3].logical_op_variables, yyvsp[-3].logical_op, yyvsp[-1].statements, yyvsp[0].statements_list); 
    }
#line 1367 "parser.tab.c"
    break;

  case 27: /* statement: DO statements UNTIL bool_expression '\n'  */
#line 134 "parser.y"
                                               {
        yyval.new_node = new Node(NodeType::DO, yyvsp[-3].statements, yyvsp[-1].logical_op_variables, yyvsp[-1].logical_op); 
    }
#line 1375 "parser.tab.c"
    break;

  case 28: /* statement: NAME '(' func_call_parameter_list ')' '\n'  */
#line 137 "parser.y"
                                                 {
        yyval.new_node = new Node(yyvsp[-4].str_val, NodeType::FUNCTION_CALL, yyvsp[-2].variables);
    }
#line 1383 "parser.tab.c"
    break;

  case 29: /* statement: RETURN expression '\n'  */
#line 140 "parser.y"
                             {
        yyval.new_node = new Node(NodeType::RETURN, yyvsp[-1].is_int_val, yyvsp[-1].is_bool_val, yyvsp[-1].is_str_val, yyvsp[-1].is_variable, yyvsp[-1].is_vector, yyvsp[-1].int_val, yyvsp[-1].str_val);
    }
#line 1391 "parser.tab.c"
    break;

  case 30: /* func_call_parameter_list: func_call_parameter_list ',' func_call_parameter  */
#line 146 "parser.y"
                                                     {
        for (auto pair: yyvsp[-2].variables)
            yyval.variables.push_back(pair);
        yyval.variables.push_back(yyvsp[0].variables.back());
    }
#line 1401 "parser.tab.c"
    break;

  case 31: /* func_call_parameter_list: func_call_parameter  */
#line 151 "parser.y"
                          {
        yyval.variables.push_back(yyvsp[0].variables.back());   
    }
#line 1409 "parser.tab.c"
    break;

  case 33: /* func_call_parameter: NAME '=' INTEGER_LITERAL  */
#line 158 "parser.y"
                             {
        yyval.variables.push_back(std::make_pair(yyvsp[-2].str_val, yyvsp[0].int_val));
    }
#line 1417 "parser.tab.c"
    break;

  case 34: /* func_call_parameter: NAME '=' BOOL_LITERAL  */
#line 161 "parser.y"
                            {
        bool bool_val = false;

        if (yyvsp[0].str_val == "true")
            bool_val = true;    
        yyval.variables.push_back(std::make_pair(yyvsp[-2].str_val, bool_val));
    }
#line 1429 "parser.tab.c"
    break;

  case 35: /* func_call_parameter: NAME '=' STRING_LITERAL  */
#line 168 "parser.y"
                              {
        yyval.variables.push_back(std::make_pair(yyvsp[-2].str_val, yyvsp[0].str_val));
    }
#line 1437 "parser.tab.c"
    break;

  case 36: /* func_call_parameter: INTEGER_LITERAL  */
#line 171 "parser.y"
                      {
        yyval.variables.push_back(std::make_pair('\0', yyvsp[0].int_val));
    }
#line 1445 "parser.tab.c"
    break;

  case 37: /* func_call_parameter: BOOL_LITERAL  */
#line 174 "parser.y"
                   {
        bool bool_val = false;

        if (yyvsp[0].str_val == "true")
            bool_val = true;
        yyval.variables.push_back(std::make_pair('\0', bool_val));
    }
#line 1457 "parser.tab.c"
    break;

  case 38: /* func_call_parameter: STRING_LITERAL  */
#line 181 "parser.y"
                     {
        yyval.variables.push_back(std::make_pair('\0', yyvsp[0].str_val));
    }
#line 1465 "parser.tab.c"
    break;

  case 39: /* else_list: else_list ELSE statements  */
#line 187 "parser.y"
                              {
        for (auto statements: yyvsp[-2].statements_list)
            yyval.statements_list.push_back(statements);
        yyval.statements_list.push_back(yyvsp[0].statements);

    }
#line 1476 "parser.tab.c"
    break;

  case 40: /* else_list: ELSE statements  */
#line 193 "parser.y"
                      {
        yyval.statements_list.push_back(yyvsp[0].statements);
    }
#line 1484 "parser.tab.c"
    break;

  case 41: /* else_list: %empty  */
#line 196 "parser.y"
      {

    }
#line 1492 "parser.tab.c"
    break;

  case 42: /* variables_list: variables_list ',' variable  */
#line 202 "parser.y"
                                {
        for (auto pair: yyvsp[-2].variables)
            yyval.variables.push_back(pair);
        yyval.variables.push_back(yyvsp[0].variables.back());
    }
#line 1502 "parser.tab.c"
    break;

  case 43: /* variables_list: variable  */
#line 207 "parser.y"
               {
        yyval.variables.push_back(yyvsp[0].variables.back());   
    }
#line 1510 "parser.tab.c"
    break;

  case 44: /* variable: NAME ASSIGN INTEGER_LITERAL  */
#line 213 "parser.y"
                                {
        yyval.variables.push_back(std::make_pair(yyvsp[-2].str_val, yyvsp[0].int_val));
    }
#line 1518 "parser.tab.c"
    break;

  case 45: /* variable: NAME ASSIGN BOOL_LITERAL  */
#line 216 "parser.y"
                               {
        bool bool_val = false;

        if (yyvsp[0].str_val == "true")
            bool_val = true;
        yyval.variables.push_back(std::make_pair(yyvsp[-2].str_val, bool_val));
    }
#line 1530 "parser.tab.c"
    break;

  case 46: /* variable: NAME ASSIGN STRING_LITERAL  */
#line 223 "parser.y"
                                 {
        yyval.variables.push_back(std::make_pair(yyvsp[-2].str_val, yyvsp[-1].str_val));
    }
#line 1538 "parser.tab.c"
    break;

  case 47: /* variable: NAME  */
#line 226 "parser.y"
           {
        yyval.variables.push_back(std::make_pair(yyvsp[0].str_val, '\0'));
    }
#line 1546 "parser.tab.c"
    break;

  case 48: /* vector_variables_list: vector_variables_list ',' vector_variable  */
#line 232 "parser.y"
                                              {
        for (auto pair: yyvsp[-2].variables)
            yyval.variables.push_back(pair);
        yyval.variables.push_back(yyvsp[0].variables.back());
    }
#line 1556 "parser.tab.c"
    break;

  case 49: /* vector_variables_list: vector_variable  */
#line 237 "parser.y"
                      {
        yyval.variables.push_back(yyvsp[0].variables.back());
    }
#line 1564 "parser.tab.c"
    break;

  case 50: /* vector_variable: NAME  */
#line 243 "parser.y"
         {
        yyval.variables.push_back(std::make_pair(yyvsp[0].str_val, '\0'));
    }
#line 1572 "parser.tab.c"
    break;

  case 51: /* bool_expression: BOOL_LITERAL  */
#line 249 "parser.y"
                 {
        bool bool_val = false;

        if (yyvsp[0].str_val == "true")
            bool_val = true;
        yyval.logical_op_variables = std::make_pair(bool_val, '\0');
    }
#line 1584 "parser.tab.c"
    break;

  case 52: /* bool_expression: expression LOGICAL_OP expression  */
#line 256 "parser.y"
                                       {
        if (yyvsp[-2].is_int_val && yyvsp[0].is_int_val) {
            yyval.logical_op_variables = std::make_pair(yyvsp[-2].int_val, yyvsp[0].int_val);
            yyval.logical_op = yyvsp[-1].str_val;
        }
        else if (yyvsp[-2].is_bool_val && yyvsp[0].is_bool_val) {
            bool first_bool_val = false;
            bool second_bool_val = false;

            if (yyvsp[-2].str_val == "true")
                first_bool_val = true;
            if (yyvsp[0].str_val == "true")
                second_bool_val = true;
            yyval.logical_op_variables = std::make_pair(first_bool_val, second_bool_val);
            yyval.logical_op = yyvsp[-1].str_val;
        }
        else if (yyvsp[-2].is_str_val && yyvsp[0].is_str_val) {
            yyval.logical_op_variables = std::make_pair(yyvsp[-2].str_val, yyvsp[0].str_val);
            yyval.logical_op = yyvsp[-1].str_val;
        }
        else {
            yyerror("Trying to execute logical operation using different types");
            return 1;
        }
    }
#line 1614 "parser.tab.c"
    break;

  case 53: /* bool_expression: expression '=' expression  */
#line 281 "parser.y"
                                {
        if (yyvsp[-2].is_int_val && yyvsp[0].is_int_val) {
            yyval.logical_op_variables = std::make_pair(yyvsp[-2].int_val, yyvsp[0].int_val);
            yyval.logical_op = "=";
        }
        else if (yyvsp[-2].is_bool_val && yyvsp[0].is_bool_val) {
            bool first_bool_val = false;
            bool second_bool_val = false;

            if (yyvsp[-2].str_val == "true")
                first_bool_val = true;
            if (yyvsp[0].str_val == "true")
                second_bool_val = true;
            yyval.logical_op_variables = std::make_pair(first_bool_val, second_bool_val);
            yyval.logical_op = "=";
        }
        else if (yyvsp[-2].is_str_val && yyvsp[0].is_str_val) {
            yyval.logical_op_variables = std::make_pair(yyvsp[-2].str_val, yyvsp[0].str_val);
            yyval.logical_op = "=";
        }
        else {
            yyerror("Trying to execute logical operation using different types");
            return 1;
        }
    }
#line 1644 "parser.tab.c"
    break;

  case 55: /* @1: %empty  */
#line 309 "parser.y"
                                          {
        if (yyvsp[-2].is_int_val && yyvsp[0].is_int_val) {
            yyval.is_int_val = true;
            
            if (yyvsp[-1].str_val == "+")
                yyval.int_val = yyvsp[-2].int_val + yyvsp[0].int_val;
            else 
                yyval.int_val = yyvsp[-2].int_val - yyvsp[0].int_val;
        } 
        else if (yyvsp[-2].is_bool_val && yyvsp[0].is_bool_val) {
            if (yyvsp[-2].str_val == "true" || yyvsp[0].str_val == "true") {
                if (yyvsp[-1].str_val == "+")
                    yyval.str_val = "true";
                else 
                    yyval.str_val = "false";
            }
            else {
                if (yyvsp[-1].str_val == "+")
                    yyval.str_val = "false";
                else 
                    yyval.str_val = "true";
            }
            yyval.is_bool_val = true;
        }
        else if (yyvsp[-2].is_str_val && yyvsp[0].is_str_val) {
            if (yyvsp[-1].str_val == "+") 
                yyval.str_val = yyvsp[-2].str_val + yyvsp[0].str_val;
            else {
                std::string result = yyvsp[-2].str_val;
                size_t pos = result.find(yyvsp[0].str_val);

                if (pos != std::string::npos)
                    result.erase(pos, yyvsp[0].str_val.length());
                yyval.str_val = result;    
            }
            yyval.is_str_val = true; 
        }
        else {
            yyerror("Trying to execute arithmetic operation using different types");
            return 1;
        }
    }
#line 1691 "parser.tab.c"
    break;

  case 56: /* expression: expression ARITHMETIC_OP expression @1 NAME '[' INTEGER_LITERAL ']'  */
#line 351 "parser.y"
                                 {
        if (yyvsp[-5].int_val < 0) {
            yyerror("Trying to access an element of a vector with a negative index");
            return 1;
        }
        yyval.is_vector = true;
        yyval.int_val = yyvsp[-5].int_val;
        yyval.str_val = yyvsp[-7].str_val;
    }
#line 1705 "parser.tab.c"
    break;

  case 57: /* expression: INTEGER_LITERAL  */
#line 360 "parser.y"
                      {
        yyval.is_int_val = true;
        yyval.int_val = yyvsp[0].int_val;
    }
#line 1714 "parser.tab.c"
    break;

  case 58: /* expression: BOOL_LITERAL  */
#line 364 "parser.y"
                   {
        yyval.is_bool_val = true;
        yyval.str_val = yyvsp[0].str_val;
    }
#line 1723 "parser.tab.c"
    break;

  case 59: /* expression: STRING_LITERAL  */
#line 368 "parser.y"
                     {
        yyval.is_str_val = true;
        yyval.str_val = yyvsp[0].str_val;
    }
#line 1732 "parser.tab.c"
    break;

  case 60: /* expression: NAME  */
#line 372 "parser.y"
           {
        yyval.is_variable = true;
        yyval.str_val = yyvsp[0].str_val;
    }
#line 1741 "parser.tab.c"
    break;


#line 1745 "parser.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 377 "parser.y"


void yyerror(std::string err_msg) {
    std::cerr << err_msg << std::endl;
}

int main() {
    if (yyparse() == 0) {
        if (is_error) {
            std::cerr << reporter.err_msg << std::endl;
            return 1;
        }
        ast.ast_prepare(); 

        if (is_error) {
            std::cerr << reporter.err_msg << std::endl;
            return 1;
        }
        ast.ast_exec();
        
        if (is_error) {
            std::cerr << reporter.err_msg << std::endl;
            return 1; 
        }
        std::cout << "Parsing completed successfully." << std::endl;
    }
    else {
        std::cerr << "Parsing failed." << std::endl;
        return 1;
    }
    return 0;
}
