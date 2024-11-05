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
#define YYPURE 2

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 2 "yacc_sql.y"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>

#include "common/log/log.h"
#include "common/lang/string.h"
#include "sql/parser/parse_defs.h"
#include "sql/parser/yacc_sql.hpp"
#include "sql/parser/lex_sql.h"
#include "sql/expr/expression.h"

using namespace std;

string token_name(const char *sql_string, YYLTYPE *llocp)
{
  return string(sql_string + llocp->first_column, llocp->last_column - llocp->first_column + 1);
}

int yyerror(YYLTYPE *llocp, const char *sql_string, ParsedSqlResult *sql_result, yyscan_t scanner, const char *msg)
{
  fprintf(stderr, "Error: %s at line %d, column %d\n", msg, llocp->first_line, llocp->first_column);
  std::unique_ptr<ParsedSqlNode> error_sql_node = std::make_unique<ParsedSqlNode>(SCF_ERROR);
  error_sql_node->error.error_msg = msg;
  error_sql_node->error.line = llocp->first_line;
  error_sql_node->error.column = llocp->first_column;
  sql_result->add_sql_node(std::move(error_sql_node));
  return 0;
}

ArithmeticExpr *create_arithmetic_expression(ArithmeticExpr::Type type,
                                             Expression *left,
                                             Expression *right,
                                             const char *sql_string,
                                             YYLTYPE *llocp)
{
  ArithmeticExpr *expr = new ArithmeticExpr(type, left, right);
  expr->set_name(token_name(sql_string, llocp));
  return expr;
}

UnboundAggregateExpr *create_aggregate_expression(const char *aggregate_name,
                                           Expression *child,
                                           const char *sql_string,
                                           YYLTYPE *llocp)
{
  UnboundAggregateExpr *expr = new UnboundAggregateExpr(aggregate_name, child);
  expr->set_name(token_name(sql_string, llocp));
  return expr;
}

UnboundVectorExpr *create_vector_expression(const char *vector_func_name,
                                     Expression *left,
                                     Expression *right,
                                     const char *sql_string,
                                     YYLTYPE *llocp)
{
  UnboundVectorExpr *expr = new UnboundVectorExpr(vector_func_name, left, right);
  expr->set_name(token_name(sql_string, llocp));
  return expr;
}


#line 137 "yacc_sql.cpp"

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

#include "yacc_sql.hpp"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_SEMICOLON = 3,                  /* SEMICOLON  */
  YYSYMBOL_BY = 4,                         /* BY  */
  YYSYMBOL_CREATE = 5,                     /* CREATE  */
  YYSYMBOL_DROP = 6,                       /* DROP  */
  YYSYMBOL_GROUP = 7,                      /* GROUP  */
  YYSYMBOL_TABLE = 8,                      /* TABLE  */
  YYSYMBOL_TABLES = 9,                     /* TABLES  */
  YYSYMBOL_INDEX = 10,                     /* INDEX  */
  YYSYMBOL_CALC = 11,                      /* CALC  */
  YYSYMBOL_SELECT = 12,                    /* SELECT  */
  YYSYMBOL_COUNT = 13,                     /* COUNT  */
  YYSYMBOL_SUM = 14,                       /* SUM  */
  YYSYMBOL_MAX = 15,                       /* MAX  */
  YYSYMBOL_MIN = 16,                       /* MIN  */
  YYSYMBOL_AVG = 17,                       /* AVG  */
  YYSYMBOL_L2_DISTANCE = 18,               /* L2_DISTANCE  */
  YYSYMBOL_COSINE_DISTANCE = 19,           /* COSINE_DISTANCE  */
  YYSYMBOL_INNER_PRODUCT = 20,             /* INNER_PRODUCT  */
  YYSYMBOL_SHOW = 21,                      /* SHOW  */
  YYSYMBOL_SYNC = 22,                      /* SYNC  */
  YYSYMBOL_INSERT = 23,                    /* INSERT  */
  YYSYMBOL_DELETE = 24,                    /* DELETE  */
  YYSYMBOL_UPDATE = 25,                    /* UPDATE  */
  YYSYMBOL_LBRACE = 26,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 27,                    /* RBRACE  */
  YYSYMBOL_COMMA = 28,                     /* COMMA  */
  YYSYMBOL_TRX_BEGIN = 29,                 /* TRX_BEGIN  */
  YYSYMBOL_TRX_COMMIT = 30,                /* TRX_COMMIT  */
  YYSYMBOL_TRX_ROLLBACK = 31,              /* TRX_ROLLBACK  */
  YYSYMBOL_INT_T = 32,                     /* INT_T  */
  YYSYMBOL_STRING_T = 33,                  /* STRING_T  */
  YYSYMBOL_FLOAT_T = 34,                   /* FLOAT_T  */
  YYSYMBOL_VECTOR_T = 35,                  /* VECTOR_T  */
  YYSYMBOL_DATE_T = 36,                    /* DATE_T  */
  YYSYMBOL_HELP = 37,                      /* HELP  */
  YYSYMBOL_EXIT = 38,                      /* EXIT  */
  YYSYMBOL_DOT = 39,                       /* DOT  */
  YYSYMBOL_INTO = 40,                      /* INTO  */
  YYSYMBOL_VALUES = 41,                    /* VALUES  */
  YYSYMBOL_FROM = 42,                      /* FROM  */
  YYSYMBOL_WHERE = 43,                     /* WHERE  */
  YYSYMBOL_AND = 44,                       /* AND  */
  YYSYMBOL_SET = 45,                       /* SET  */
  YYSYMBOL_INNER = 46,                     /* INNER  */
  YYSYMBOL_JOIN = 47,                      /* JOIN  */
  YYSYMBOL_ON = 48,                        /* ON  */
  YYSYMBOL_LOAD = 49,                      /* LOAD  */
  YYSYMBOL_DATA = 50,                      /* DATA  */
  YYSYMBOL_INFILE = 51,                    /* INFILE  */
  YYSYMBOL_EXPLAIN = 52,                   /* EXPLAIN  */
  YYSYMBOL_STORAGE = 53,                   /* STORAGE  */
  YYSYMBOL_FORMAT = 54,                    /* FORMAT  */
  YYSYMBOL_EQ = 55,                        /* EQ  */
  YYSYMBOL_LT = 56,                        /* LT  */
  YYSYMBOL_GT = 57,                        /* GT  */
  YYSYMBOL_LE = 58,                        /* LE  */
  YYSYMBOL_GE = 59,                        /* GE  */
  YYSYMBOL_NE = 60,                        /* NE  */
  YYSYMBOL_NOT = 61,                       /* NOT  */
  YYSYMBOL_IS = 62,                        /* IS  */
  YYSYMBOL_AS = 63,                        /* AS  */
  YYSYMBOL_IN = 64,                        /* IN  */
  YYSYMBOL_ASC = 65,                       /* ASC  */
  YYSYMBOL_DESC = 66,                      /* DESC  */
  YYSYMBOL_ORDER = 67,                     /* ORDER  */
  YYSYMBOL_EXISTS = 68,                    /* EXISTS  */
  YYSYMBOL_NULL_T = 69,                    /* NULL_T  */
  YYSYMBOL_LIKE = 70,                      /* LIKE  */
  YYSYMBOL_NUMBER = 71,                    /* NUMBER  */
  YYSYMBOL_FLOAT = 72,                     /* FLOAT  */
  YYSYMBOL_ID = 73,                        /* ID  */
  YYSYMBOL_SSS = 74,                       /* SSS  */
  YYSYMBOL_75_ = 75,                       /* '+'  */
  YYSYMBOL_76_ = 76,                       /* '-'  */
  YYSYMBOL_77_ = 77,                       /* '*'  */
  YYSYMBOL_78_ = 78,                       /* '/'  */
  YYSYMBOL_UMINUS = 79,                    /* UMINUS  */
  YYSYMBOL_YYACCEPT = 80,                  /* $accept  */
  YYSYMBOL_commands = 81,                  /* commands  */
  YYSYMBOL_command_wrapper = 82,           /* command_wrapper  */
  YYSYMBOL_exit_stmt = 83,                 /* exit_stmt  */
  YYSYMBOL_help_stmt = 84,                 /* help_stmt  */
  YYSYMBOL_sync_stmt = 85,                 /* sync_stmt  */
  YYSYMBOL_begin_stmt = 86,                /* begin_stmt  */
  YYSYMBOL_commit_stmt = 87,               /* commit_stmt  */
  YYSYMBOL_rollback_stmt = 88,             /* rollback_stmt  */
  YYSYMBOL_drop_table_stmt = 89,           /* drop_table_stmt  */
  YYSYMBOL_show_tables_stmt = 90,          /* show_tables_stmt  */
  YYSYMBOL_desc_table_stmt = 91,           /* desc_table_stmt  */
  YYSYMBOL_create_index_stmt = 92,         /* create_index_stmt  */
  YYSYMBOL_idx_col_list = 93,              /* idx_col_list  */
  YYSYMBOL_drop_index_stmt = 94,           /* drop_index_stmt  */
  YYSYMBOL_create_table_stmt = 95,         /* create_table_stmt  */
  YYSYMBOL_attr_def_list = 96,             /* attr_def_list  */
  YYSYMBOL_attr_def = 97,                  /* attr_def  */
  YYSYMBOL_nullable = 98,                  /* nullable  */
  YYSYMBOL_number = 99,                    /* number  */
  YYSYMBOL_type = 100,                     /* type  */
  YYSYMBOL_insert_stmt = 101,              /* insert_stmt  */
  YYSYMBOL_value_list = 102,               /* value_list  */
  YYSYMBOL_value = 103,                    /* value  */
  YYSYMBOL_storage_format = 104,           /* storage_format  */
  YYSYMBOL_delete_stmt = 105,              /* delete_stmt  */
  YYSYMBOL_assignment = 106,               /* assignment  */
  YYSYMBOL_assignment_list = 107,          /* assignment_list  */
  YYSYMBOL_update_stmt = 108,              /* update_stmt  */
  YYSYMBOL_join_node_list = 109,           /* join_node_list  */
  YYSYMBOL_join_node = 110,                /* join_node  */
  YYSYMBOL_join_list = 111,                /* join_list  */
  YYSYMBOL_select_stmt = 112,              /* select_stmt  */
  YYSYMBOL_order_by = 113,                 /* order_by  */
  YYSYMBOL_sort_unit_list = 114,           /* sort_unit_list  */
  YYSYMBOL_sort_unit = 115,                /* sort_unit  */
  YYSYMBOL_calc_stmt = 116,                /* calc_stmt  */
  YYSYMBOL_alias = 117,                    /* alias  */
  YYSYMBOL_expression_list = 118,          /* expression_list  */
  YYSYMBOL_expression = 119,               /* expression  */
  YYSYMBOL_aggregation_func = 120,         /* aggregation_func  */
  YYSYMBOL_aggregation_name = 121,         /* aggregation_name  */
  YYSYMBOL_vector_func = 122,              /* vector_func  */
  YYSYMBOL_vector_func_name = 123,         /* vector_func_name  */
  YYSYMBOL_rel_attr = 124,                 /* rel_attr  */
  YYSYMBOL_where = 125,                    /* where  */
  YYSYMBOL_condition_list = 126,           /* condition_list  */
  YYSYMBOL_condition = 127,                /* condition  */
  YYSYMBOL_comp_op = 128,                  /* comp_op  */
  YYSYMBOL_group_by = 129,                 /* group_by  */
  YYSYMBOL_load_data_stmt = 130,           /* load_data_stmt  */
  YYSYMBOL_explain_stmt = 131,             /* explain_stmt  */
  YYSYMBOL_set_variable_stmt = 132,        /* set_variable_stmt  */
  YYSYMBOL_opt_semicolon = 133             /* opt_semicolon  */
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
typedef yytype_uint8 yy_state_t;

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

#if 1

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
#endif /* 1 */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE) \
             + YYSIZEOF (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

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
#define YYFINAL  78
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   257

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  80
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  54
/* YYNRULES -- Number of rules.  */
#define YYNRULES  136
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  237

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   330


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
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,    77,    75,     2,    76,     2,    78,     2,     2,
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
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      79
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   243,   243,   251,   252,   253,   254,   255,   256,   257,
     258,   259,   260,   261,   262,   263,   264,   265,   266,   267,
     268,   269,   270,   274,   280,   285,   291,   297,   303,   309,
     316,   322,   330,   352,   355,   368,   378,   402,   405,   418,
     431,   444,   445,   447,   452,   455,   456,   457,   458,   459,
     462,   485,   488,   505,   509,   513,   519,   525,   528,   535,
     548,   556,   561,   574,   593,   596,   607,   625,   628,   646,
     681,   684,   691,   697,   710,   716,   722,   731,   741,   744,
     748,   755,   758,   766,   780,   783,   786,   789,   792,   800,
     803,   808,   814,   817,   821,   824,   827,   833,   844,   845,
     846,   847,   848,   852,   857,   858,   859,   863,   868,   879,
     882,   889,   892,   897,   904,   912,   922,   935,   936,   937,
     938,   939,   940,   941,   942,   943,   944,   945,   946,   947,
     948,   954,   959,   972,   980,   990,   991
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "SEMICOLON", "BY",
  "CREATE", "DROP", "GROUP", "TABLE", "TABLES", "INDEX", "CALC", "SELECT",
  "COUNT", "SUM", "MAX", "MIN", "AVG", "L2_DISTANCE", "COSINE_DISTANCE",
  "INNER_PRODUCT", "SHOW", "SYNC", "INSERT", "DELETE", "UPDATE", "LBRACE",
  "RBRACE", "COMMA", "TRX_BEGIN", "TRX_COMMIT", "TRX_ROLLBACK", "INT_T",
  "STRING_T", "FLOAT_T", "VECTOR_T", "DATE_T", "HELP", "EXIT", "DOT",
  "INTO", "VALUES", "FROM", "WHERE", "AND", "SET", "INNER", "JOIN", "ON",
  "LOAD", "DATA", "INFILE", "EXPLAIN", "STORAGE", "FORMAT", "EQ", "LT",
  "GT", "LE", "GE", "NE", "NOT", "IS", "AS", "IN", "ASC", "DESC", "ORDER",
  "EXISTS", "NULL_T", "LIKE", "NUMBER", "FLOAT", "ID", "SSS", "'+'", "'-'",
  "'*'", "'/'", "UMINUS", "$accept", "commands", "command_wrapper",
  "exit_stmt", "help_stmt", "sync_stmt", "begin_stmt", "commit_stmt",
  "rollback_stmt", "drop_table_stmt", "show_tables_stmt",
  "desc_table_stmt", "create_index_stmt", "idx_col_list",
  "drop_index_stmt", "create_table_stmt", "attr_def_list", "attr_def",
  "nullable", "number", "type", "insert_stmt", "value_list", "value",
  "storage_format", "delete_stmt", "assignment", "assignment_list",
  "update_stmt", "join_node_list", "join_node", "join_list", "select_stmt",
  "order_by", "sort_unit_list", "sort_unit", "calc_stmt", "alias",
  "expression_list", "expression", "aggregation_func", "aggregation_name",
  "vector_func", "vector_func_name", "rel_attr", "where", "condition_list",
  "condition", "comp_op", "group_by", "load_data_stmt", "explain_stmt",
  "set_variable_stmt", "opt_semicolon", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-175)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     180,    29,    67,   107,   107,     8,  -175,   -18,     6,    -5,
    -175,  -175,  -175,  -175,  -175,    10,    31,   180,    11,    56,
      82,  -175,  -175,  -175,  -175,  -175,  -175,  -175,  -175,  -175,
    -175,  -175,  -175,  -175,  -175,  -175,  -175,  -175,  -175,  -175,
    -175,    18,    19,    21,    23,  -175,  -175,  -175,  -175,  -175,
    -175,  -175,  -175,    -7,  -175,  -175,  -175,    68,  -175,   107,
    -175,  -175,  -175,   -48,  -175,    80,  -175,    83,  -175,    66,
    -175,    38,    39,    69,    60,    65,  -175,  -175,  -175,  -175,
    -175,    91,    86,  -175,    88,   103,   104,   -31,  -175,    59,
    -175,   107,   107,   107,   107,   109,   107,   107,    70,   101,
     108,    71,   -51,    85,    89,    90,    92,  -175,  -175,  -175,
    -175,  -175,     1,     1,  -175,  -175,   107,   137,    -4,   -47,
     138,   141,    84,  -175,   113,   144,   108,  -175,   129,   114,
     145,   148,  -175,  -175,  -175,   107,   131,    70,   108,   107,
     119,   107,   179,  -175,   146,   107,    71,  -175,   167,  -175,
    -175,  -175,  -175,  -175,   -12,    89,   155,   115,   -24,   142,
    -175,   138,   126,    12,   107,   -17,  -175,  -175,  -175,  -175,
    -175,  -175,   -23,   133,  -175,  -175,  -175,   107,    84,   -17,
    -175,   122,   125,   128,  -175,  -175,   145,   147,   170,  -175,
     134,  -175,   195,  -175,   107,   181,   -17,  -175,  -175,  -175,
    -175,   -17,  -175,  -175,  -175,   185,  -175,  -175,   152,  -175,
     140,   187,   -47,   107,  -175,    12,  -175,   -25,   160,   170,
    -175,   168,  -175,   191,    63,  -175,  -175,   149,  -175,    84,
     107,  -175,  -175,  -175,   131,  -175,  -175
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,    81,    81,     0,    25,     0,     0,     0,
      26,    27,    28,    24,    23,     0,     0,     0,     0,     0,
     135,    22,    21,    14,    15,    16,    17,     9,    10,    11,
      12,    13,     8,     5,     7,     6,     4,     3,    18,    19,
      20,     0,     0,     0,     0,    98,    99,   100,   101,   102,
     104,   105,   106,    81,    56,    53,    54,   107,    55,     0,
      92,    90,    77,    78,    94,     0,    95,     0,    91,     0,
      30,     0,     0,     0,     0,     0,   133,    31,     1,   136,
       2,     0,     0,    29,     0,     0,     0,     0,    89,     0,
      79,     0,     0,     0,     0,    82,    81,     0,     0,     0,
     109,     0,     0,     0,     0,     0,     0,    96,    88,   108,
      93,    80,    84,    85,    86,    87,    81,     0,     0,    78,
      64,     0,   111,    59,     0,    61,   109,   134,     0,     0,
      37,     0,    35,    83,    97,     0,    67,     0,   109,     0,
       0,     0,     0,   110,   112,     0,     0,    63,     0,    45,
      46,    47,    49,    48,    41,     0,     0,     0,     0,     0,
      66,    64,    70,    51,     0,   115,   117,   118,   119,   120,
     121,   122,     0,   125,   127,   129,   123,     0,   111,    60,
      62,     0,     0,     0,    42,    40,    37,    57,    33,   103,
       0,    65,     0,   131,     0,     0,   116,   128,   130,   124,
     126,   114,   113,   132,    44,     0,    43,    38,     0,    36,
       0,     0,    78,     0,    69,    51,    50,    41,     0,    33,
      32,     0,    71,    72,    74,    52,    39,     0,    34,   111,
       0,    75,    76,    58,    67,    73,    68
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -175,  -175,   203,  -175,  -175,  -175,  -175,  -175,  -175,  -175,
    -175,  -175,  -175,     2,  -175,  -175,    37,    72,     7,  -175,
    -175,  -175,    13,   124,  -175,  -175,  -175,    87,  -175,    81,
      93,    14,   178,  -175,    15,  -175,  -175,  -117,    -3,   -59,
    -175,  -175,  -175,  -175,  -175,   -95,  -174,  -175,  -175,  -175,
    -175,  -175,  -175,  -175
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,   211,    31,    32,   156,   130,   185,   205,
     154,    33,   195,    61,   209,    34,   125,   126,    35,   138,
     120,   160,    36,   193,   222,   223,    37,    95,    62,    63,
      64,    65,    66,    67,    68,   123,   143,   144,   177,   214,
      38,    39,    40,    80
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      88,    69,   136,   189,   202,     4,    45,    46,    47,    48,
      49,    50,    51,    52,   182,    89,    89,    70,    54,    53,
      55,    56,    71,    58,   135,    90,    90,    91,    92,    93,
      94,   147,   112,   113,   114,   115,   183,    41,   118,    42,
     194,   197,   109,   162,   184,   198,   110,   199,    72,   183,
      86,    91,    92,    93,    94,   234,    78,   184,    91,    92,
      93,    94,    54,   142,    55,    56,    57,    58,    73,    59,
      60,    91,    92,    93,    94,    43,   158,    44,    93,    94,
     163,    75,   165,    74,    77,    79,   179,    91,    92,    93,
      94,    81,    82,   117,    83,   221,    84,    45,    46,    47,
      48,    49,    50,    51,    52,   196,    96,    87,    98,    97,
      53,    99,   100,   133,   101,   102,   103,   104,   201,   142,
      45,    46,    47,    48,    49,    50,    51,    52,   231,   232,
     107,   108,   111,    53,   105,   215,   106,   116,    91,    92,
      93,    94,   121,   119,   124,   140,   149,   150,   151,   152,
     153,   122,   141,    54,   224,    55,    56,    57,    58,   128,
      59,    60,   129,   131,   134,   132,   137,   139,   145,   148,
     142,   224,   146,   155,   157,   181,    54,   159,    55,    56,
      57,    58,   187,    59,    60,     1,     2,   164,   188,   190,
     178,     3,     4,   192,   200,   203,   204,   206,   210,   213,
     208,     5,     6,     7,     8,     9,   218,   212,   216,    10,
      11,    12,   217,   219,   220,   227,   229,    13,    14,   230,
      76,   228,   233,   207,   226,    15,   127,   186,   225,    16,
     161,    85,    17,   180,   166,   167,   168,   169,   170,   171,
     172,   173,   191,   174,     0,   235,    18,   175,   236,   176,
       0,     0,     0,     0,    91,    92,    93,    94
};

static const yytype_int16 yycheck[] =
{
      59,     4,   119,    27,   178,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    26,    63,    63,     9,    69,    26,
      71,    72,    40,    74,    28,    73,    73,    75,    76,    77,
      78,   126,    91,    92,    93,    94,    61,     8,    97,    10,
      28,    64,    73,   138,    69,    68,    77,    70,    42,    61,
      53,    75,    76,    77,    78,   229,     0,    69,    75,    76,
      77,    78,    69,   122,    71,    72,    73,    74,    73,    76,
      77,    75,    76,    77,    78,     8,   135,    10,    77,    78,
     139,    50,   141,    73,    73,     3,   145,    75,    76,    77,
      78,    73,    73,    96,    73,   212,    73,    13,    14,    15,
      16,    17,    18,    19,    20,   164,    26,    39,    42,    26,
      26,    73,    73,   116,    45,    55,    51,    26,   177,   178,
      13,    14,    15,    16,    17,    18,    19,    20,    65,    66,
      27,    27,    73,    26,    48,   194,    48,    28,    75,    76,
      77,    78,    41,    73,    73,    61,    32,    33,    34,    35,
      36,    43,    68,    69,   213,    71,    72,    73,    74,    74,
      76,    77,    73,    73,    27,    73,    28,    26,    55,    40,
     229,   230,    28,    28,    26,     8,    69,    46,    71,    72,
      73,    74,    27,    76,    77,     5,     6,    68,    73,    47,
      44,    11,    12,    67,    61,    73,    71,    69,    28,     4,
      53,    21,    22,    23,    24,    25,    54,    73,    27,    29,
      30,    31,    27,    73,    27,    55,    48,    37,    38,    28,
      17,   219,    73,   186,   217,    45,   102,   155,   215,    49,
     137,    53,    52,   146,    55,    56,    57,    58,    59,    60,
      61,    62,   161,    64,    -1,   230,    66,    68,   234,    70,
      -1,    -1,    -1,    -1,    75,    76,    77,    78
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     5,     6,    11,    12,    21,    22,    23,    24,    25,
      29,    30,    31,    37,    38,    45,    49,    52,    66,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    94,    95,   101,   105,   108,   112,   116,   130,   131,
     132,     8,    10,     8,    10,    13,    14,    15,    16,    17,
      18,    19,    20,    26,    69,    71,    72,    73,    74,    76,
      77,   103,   118,   119,   120,   121,   122,   123,   124,   118,
       9,    40,    42,    73,    73,    50,    82,    73,     0,     3,
     133,    73,    73,    73,    73,   112,   118,    39,   119,    63,
      73,    75,    76,    77,    78,   117,    26,    26,    42,    73,
      73,    45,    55,    51,    26,    48,    48,    27,    27,    73,
      77,    73,   119,   119,   119,   119,    28,   118,   119,    73,
     110,    41,    43,   125,    73,   106,   107,   103,    74,    73,
      97,    73,    73,   118,    27,    28,   117,    28,   109,    26,
      61,    68,   119,   126,   127,    55,    28,   125,    40,    32,
      33,    34,    35,    36,   100,    28,    96,    26,   119,    46,
     111,   110,   125,   119,    68,   119,    55,    56,    57,    58,
      59,    60,    61,    62,    64,    68,    70,   128,    44,   119,
     107,     8,    26,    61,    69,    98,    97,    27,    73,    27,
      47,   109,    67,   113,    28,   102,   119,    64,    68,    70,
      61,   119,   126,    73,    71,    99,    69,    96,    53,   104,
      28,    93,    73,     4,   129,   119,    27,    27,    54,    73,
      27,   117,   114,   115,   119,   102,    98,    55,    93,    48,
      28,    65,    66,    73,   126,   114,   111
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    80,    81,    82,    82,    82,    82,    82,    82,    82,
      82,    82,    82,    82,    82,    82,    82,    82,    82,    82,
      82,    82,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    93,    94,    95,    96,    96,    97,
      97,    98,    98,    98,    99,   100,   100,   100,   100,   100,
     101,   102,   102,   103,   103,   103,   103,   104,   104,   105,
     106,   107,   107,   108,   109,   109,   110,   111,   111,   112,
     113,   113,   114,   114,   115,   115,   115,   116,   117,   117,
     117,   118,   118,   118,   119,   119,   119,   119,   119,   119,
     119,   119,   119,   119,   119,   119,   119,   120,   121,   121,
     121,   121,   121,   122,   123,   123,   123,   124,   124,   125,
     125,   126,   126,   126,   127,   127,   127,   128,   128,   128,
     128,   128,   128,   128,   128,   128,   128,   128,   128,   128,
     128,   129,   130,   131,   132,   133,   133
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       2,     2,     9,     0,     3,     5,     8,     0,     3,     6,
       3,     0,     1,     2,     1,     1,     1,     1,     1,     1,
       8,     0,     3,     1,     1,     1,     1,     0,     4,     4,
       3,     1,     3,     5,     0,     3,     3,     0,     7,     8,
       0,     3,     1,     3,     1,     2,     2,     2,     0,     1,
       2,     0,     2,     4,     3,     3,     3,     3,     3,     2,
       1,     1,     1,     3,     1,     1,     3,     4,     1,     1,
       1,     1,     1,     6,     1,     1,     1,     1,     3,     0,
       2,     0,     1,     3,     3,     2,     3,     1,     1,     1,
       1,     1,     1,     1,     2,     1,     2,     1,     2,     1,
       2,     0,     7,     2,     4,     0,     1
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
        yyerror (&yylloc, sql_string, sql_result, scanner, YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF

/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


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


/* YYLOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

# ifndef YYLOCATION_PRINT

#  if defined YY_LOCATION_PRINT

   /* Temporary convenience wrapper in case some people defined the
      undocumented and private YY_LOCATION_PRINT macros.  */
#   define YYLOCATION_PRINT(File, Loc)  YY_LOCATION_PRINT(File, *(Loc))

#  elif defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
}

#   define YYLOCATION_PRINT  yy_location_print_

    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT(File, Loc)  YYLOCATION_PRINT(File, &(Loc))

#  else

#   define YYLOCATION_PRINT(File, Loc) ((void) 0)
    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT  YYLOCATION_PRINT

#  endif
# endif /* !defined YYLOCATION_PRINT */


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, Location, sql_string, sql_result, scanner); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (yylocationp);
  YY_USE (sql_string);
  YY_USE (sql_result);
  YY_USE (scanner);
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
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  YYLOCATION_PRINT (yyo, yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yykind, yyvaluep, yylocationp, sql_string, sql_result, scanner);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp,
                 int yyrule, const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
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
                       &yyvsp[(yyi + 1) - (yynrhs)],
                       &(yylsp[(yyi + 1) - (yynrhs)]), sql_string, sql_result, scanner);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule, sql_string, sql_result, scanner); \
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


/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yysymbol_kind_t yytoken;
  YYLTYPE *yylloc;
} yypcontext_t;

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYCTX, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
   Return 0 if there are more than YYARGN expected tokens, yet fill
   YYARG up to YYARGN. */
static int
yypcontext_expected_tokens (const yypcontext_t *yyctx,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  int yyn = yypact[+*yyctx->yyssp];
  if (!yypact_value_is_default (yyn))
    {
      /* Start YYX at -YYN if negative to avoid negative indexes in
         YYCHECK.  In other words, skip the first -YYN actions for
         this state because they are default actions.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;
      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yyx;
      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
        if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror
            && !yytable_value_is_error (yytable[yyx + yyn]))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = YY_CAST (yysymbol_kind_t, yyx);
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}




#ifndef yystrlen
# if defined __GLIBC__ && defined _STRING_H
#  define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
# else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
# endif
#endif

#ifndef yystpcpy
# if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#  define yystpcpy stpcpy
# else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
# endif
#endif

#ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;
      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
#endif


static int
yy_syntax_error_arguments (const yypcontext_t *yyctx,
                           yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
    {
      int yyn;
      if (yyarg)
        yyarg[yycount] = yyctx->yytoken;
      ++yycount;
      yyn = yypcontext_expected_tokens (yyctx,
                                        yyarg ? yyarg + 1 : yyarg, yyargn - 1);
      if (yyn == YYENOMEM)
        return YYENOMEM;
      else
        yycount += yyn;
    }
  return yycount;
}

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                const yypcontext_t *yyctx)
{
  enum { YYARGS_MAX = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  yysymbol_kind_t yyarg[YYARGS_MAX];
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* Actual size of YYARG. */
  int yycount = yy_syntax_error_arguments (yyctx, yyarg, YYARGS_MAX);
  if (yycount == YYENOMEM)
    return YYENOMEM;

  switch (yycount)
    {
#define YYCASE_(N, S)                       \
      case N:                               \
        yyformat = S;                       \
        break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
    }

  /* Compute error message size.  Don't count the "%s"s, but reserve
     room for the terminator.  */
  yysize = yystrlen (yyformat) - 2 * yycount + 1;
  {
    int yyi;
    for (yyi = 0; yyi < yycount; ++yyi)
      {
        YYPTRDIFF_T yysize1
          = yysize + yytnamerr (YY_NULLPTR, yytname[yyarg[yyi]]);
        if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
          yysize = yysize1;
        else
          return YYENOMEM;
      }
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return -1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yytname[yyarg[yyi++]]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, YYLTYPE *yylocationp, const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
  YY_USE (yyvaluep);
  YY_USE (yylocationp);
  YY_USE (sql_string);
  YY_USE (sql_result);
  YY_USE (scanner);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}






/*----------.
| yyparse.  |
`----------*/

int
yyparse (const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
/* Lookahead token kind.  */
int yychar;


/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
YY_INITIAL_VALUE (static YYSTYPE yyval_default;)
YYSTYPE yylval YY_INITIAL_VALUE (= yyval_default);

/* Location data for the lookahead symbol.  */
static YYLTYPE yyloc_default
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
YYLTYPE yylloc = yyloc_default;

    /* Number of syntax errors so far.  */
    int yynerrs = 0;

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

    /* The location stack: array, bottom, top.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls = yylsa;
    YYLTYPE *yylsp = yyls;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[3];

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  yylsp[0] = yylloc;
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
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yyls1, yysize * YYSIZEOF (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
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
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

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
      yychar = yylex (&yylval, &yylloc, scanner);
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
      yyerror_range[1] = yylloc;
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
  *++yylsp = yylloc;

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

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* commands: command_wrapper opt_semicolon  */
#line 244 "yacc_sql.y"
  {
    std::unique_ptr<ParsedSqlNode> sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[-1].sql_node));
    sql_result->add_sql_node(std::move(sql_node));
  }
#line 1844 "yacc_sql.cpp"
    break;

  case 23: /* exit_stmt: EXIT  */
#line 274 "yacc_sql.y"
         {
      (void)yynerrs;  // 这么写为了消除yynerrs未使用的告警。如果你有更好的方法欢迎提PR
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXIT);
    }
#line 1853 "yacc_sql.cpp"
    break;

  case 24: /* help_stmt: HELP  */
#line 280 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_HELP);
    }
#line 1861 "yacc_sql.cpp"
    break;

  case 25: /* sync_stmt: SYNC  */
#line 285 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SYNC);
    }
#line 1869 "yacc_sql.cpp"
    break;

  case 26: /* begin_stmt: TRX_BEGIN  */
#line 291 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_BEGIN);
    }
#line 1877 "yacc_sql.cpp"
    break;

  case 27: /* commit_stmt: TRX_COMMIT  */
#line 297 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_COMMIT);
    }
#line 1885 "yacc_sql.cpp"
    break;

  case 28: /* rollback_stmt: TRX_ROLLBACK  */
#line 303 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_ROLLBACK);
    }
#line 1893 "yacc_sql.cpp"
    break;

  case 29: /* drop_table_stmt: DROP TABLE ID  */
#line 309 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_TABLE);
      (yyval.sql_node)->drop_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1903 "yacc_sql.cpp"
    break;

  case 30: /* show_tables_stmt: SHOW TABLES  */
#line 316 "yacc_sql.y"
                {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SHOW_TABLES);
    }
#line 1911 "yacc_sql.cpp"
    break;

  case 31: /* desc_table_stmt: DESC ID  */
#line 322 "yacc_sql.y"
             {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DESC_TABLE);
      (yyval.sql_node)->desc_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1921 "yacc_sql.cpp"
    break;

  case 32: /* create_index_stmt: CREATE INDEX ID ON ID LBRACE ID idx_col_list RBRACE  */
#line 331 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_INDEX);
      CreateIndexSqlNode &create_index = (yyval.sql_node)->create_index;
      create_index.index_name = (yyvsp[-6].string);
      create_index.relation_name = (yyvsp[-4].string);
      
      std::vector<std::string> *idx_cols = (yyvsp[-1].relation_list);
      if (nullptr != idx_cols) {
        create_index.attr_names.swap(*idx_cols);
        delete (yyvsp[-1].relation_list);
      }
      create_index.attr_names.emplace_back((yyvsp[-2].string));
      std::reverse(create_index.attr_names.begin(), create_index.attr_names.end());
      free((yyvsp[-6].string));
      free((yyvsp[-4].string));
      free((yyvsp[-2].string));
    }
#line 1943 "yacc_sql.cpp"
    break;

  case 33: /* idx_col_list: %empty  */
#line 352 "yacc_sql.y"
    {
      (yyval.relation_list) = nullptr;
    }
#line 1951 "yacc_sql.cpp"
    break;

  case 34: /* idx_col_list: COMMA ID idx_col_list  */
#line 356 "yacc_sql.y"
    {
      if ((yyvsp[0].relation_list) != nullptr) {
        (yyval.relation_list) = (yyvsp[0].relation_list);
      } else {
        (yyval.relation_list) = new std::vector<std::string>;
      }
      (yyval.relation_list)->emplace_back((yyvsp[-1].string));
      free((yyvsp[-1].string));
    }
#line 1965 "yacc_sql.cpp"
    break;

  case 35: /* drop_index_stmt: DROP INDEX ID ON ID  */
#line 369 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_INDEX);
      (yyval.sql_node)->drop_index.index_name = (yyvsp[-2].string);
      (yyval.sql_node)->drop_index.relation_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 1977 "yacc_sql.cpp"
    break;

  case 36: /* create_table_stmt: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE storage_format  */
#line 379 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_TABLE);
      CreateTableSqlNode &create_table = (yyval.sql_node)->create_table;
      create_table.relation_name = (yyvsp[-5].string);
      free((yyvsp[-5].string));

      std::vector<AttrInfoSqlNode> *src_attrs = (yyvsp[-2].attr_infos);

      if (src_attrs != nullptr) {
        create_table.attr_infos.swap(*src_attrs);
        delete src_attrs;
      }
      create_table.attr_infos.emplace_back(*(yyvsp[-3].attr_info));
      std::reverse(create_table.attr_infos.begin(), create_table.attr_infos.end());
      delete (yyvsp[-3].attr_info);
      if ((yyvsp[0].string) != nullptr) {
        create_table.storage_format = (yyvsp[0].string);
        free((yyvsp[0].string));
      }
    }
#line 2002 "yacc_sql.cpp"
    break;

  case 37: /* attr_def_list: %empty  */
#line 402 "yacc_sql.y"
    {
      (yyval.attr_infos) = nullptr;
    }
#line 2010 "yacc_sql.cpp"
    break;

  case 38: /* attr_def_list: COMMA attr_def attr_def_list  */
#line 406 "yacc_sql.y"
    {
      if ((yyvsp[0].attr_infos) != nullptr) {
        (yyval.attr_infos) = (yyvsp[0].attr_infos);
      } else {
        (yyval.attr_infos) = new std::vector<AttrInfoSqlNode>;
      }
      (yyval.attr_infos)->emplace_back(*(yyvsp[-1].attr_info));
      delete (yyvsp[-1].attr_info);
    }
#line 2024 "yacc_sql.cpp"
    break;

  case 39: /* attr_def: ID type LBRACE number RBRACE nullable  */
#line 419 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-4].number);
      (yyval.attr_info)->name = (yyvsp[-5].string);
      (yyval.attr_info)->nullable = (yyvsp[0].boolean);
      if ((yyvsp[-4].number) == static_cast<int>(AttrType::VECTORS)) { // 向量的字节长度为元素个数4倍
        (yyval.attr_info)->length = (yyvsp[-2].number) * 4 + 2; // 对于向量类型，用倒数第二个字节表示标志位是否为空
      } else {
        (yyval.attr_info)->length = (yyvsp[-2].number) + 1;
      }
      free((yyvsp[-5].string));
    }
#line 2041 "yacc_sql.cpp"
    break;

  case 40: /* attr_def: ID type nullable  */
#line 432 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-1].number);
      (yyval.attr_info)->name = (yyvsp[-2].string);
      (yyval.attr_info)->length = 4 + 1; // 用最后一个字节表示标志位是否为空
      (yyval.attr_info)->nullable = (yyvsp[0].boolean);
      free((yyvsp[-2].string));
    }
#line 2054 "yacc_sql.cpp"
    break;

  case 41: /* nullable: %empty  */
#line 444 "yacc_sql.y"
    { (yyval.boolean) = false; }
#line 2060 "yacc_sql.cpp"
    break;

  case 42: /* nullable: NULL_T  */
#line 446 "yacc_sql.y"
    { (yyval.boolean) = true; }
#line 2066 "yacc_sql.cpp"
    break;

  case 43: /* nullable: NOT NULL_T  */
#line 448 "yacc_sql.y"
    { (yyval.boolean) = false; }
#line 2072 "yacc_sql.cpp"
    break;

  case 44: /* number: NUMBER  */
#line 452 "yacc_sql.y"
           {(yyval.number) = (yyvsp[0].number);}
#line 2078 "yacc_sql.cpp"
    break;

  case 45: /* type: INT_T  */
#line 455 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::INTS); }
#line 2084 "yacc_sql.cpp"
    break;

  case 46: /* type: STRING_T  */
#line 456 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::CHARS); }
#line 2090 "yacc_sql.cpp"
    break;

  case 47: /* type: FLOAT_T  */
#line 457 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::FLOATS); }
#line 2096 "yacc_sql.cpp"
    break;

  case 48: /* type: DATE_T  */
#line 458 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::DATES); }
#line 2102 "yacc_sql.cpp"
    break;

  case 49: /* type: VECTOR_T  */
#line 459 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::VECTORS); }
#line 2108 "yacc_sql.cpp"
    break;

  case 50: /* insert_stmt: INSERT INTO ID VALUES LBRACE expression value_list RBRACE  */
#line 463 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_INSERT);
      (yyval.sql_node)->insertion.relation_name = (yyvsp[-5].string);
      if ((yyvsp[-1].value_list) != nullptr) {
        (yyval.sql_node)->insertion.values.swap(*(yyvsp[-1].value_list));
        delete (yyvsp[-1].value_list);
      }
      Value value;
      if ((yyvsp[-2].expression)->try_get_value(value) == RC::SUCCESS) { // 假设表达式都是常量表达式，需要从中获取常量
        (yyval.sql_node)->insertion.values.emplace_back(value);
      } else {
        yyerror(&(yyloc), sql_string, sql_result, scanner, "Failed to convert expression to value in insert statement");
        YYERROR;
      }
      std::reverse((yyval.sql_node)->insertion.values.begin(), (yyval.sql_node)->insertion.values.end());
      delete (yyvsp[-2].expression);
      free((yyvsp[-5].string));
    }
#line 2131 "yacc_sql.cpp"
    break;

  case 51: /* value_list: %empty  */
#line 485 "yacc_sql.y"
    {
      (yyval.value_list) = nullptr;
    }
#line 2139 "yacc_sql.cpp"
    break;

  case 52: /* value_list: COMMA expression value_list  */
#line 488 "yacc_sql.y"
                                   { 
      if ((yyvsp[0].value_list) != nullptr) {
        (yyval.value_list) = (yyvsp[0].value_list);
      } else {
        (yyval.value_list) = new std::vector<Value>;
      }
      Value value;
      if ((yyvsp[-1].expression)->try_get_value(value) == RC::SUCCESS) {
        (yyval.value_list)->emplace_back(value);
      } else {
        yyerror(&(yyloc), sql_string, sql_result, scanner, "Failed to convert expression to value in insert statement");
        YYERROR;
      }
      delete (yyvsp[-1].expression);
    }
#line 2159 "yacc_sql.cpp"
    break;

  case 53: /* value: NUMBER  */
#line 505 "yacc_sql.y"
           {
      (yyval.value) = new Value((int)(yyvsp[0].number));
      (yyloc) = (yylsp[0]);
    }
#line 2168 "yacc_sql.cpp"
    break;

  case 54: /* value: FLOAT  */
#line 509 "yacc_sql.y"
           {
      (yyval.value) = new Value((float)(yyvsp[0].floats));
      (yyloc) = (yylsp[0]);
    }
#line 2177 "yacc_sql.cpp"
    break;

  case 55: /* value: SSS  */
#line 513 "yacc_sql.y"
         {
      char *tmp = common::substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
      (yyval.value) = new Value(tmp);
      free(tmp);
      free((yyvsp[0].string));
    }
#line 2188 "yacc_sql.cpp"
    break;

  case 56: /* value: NULL_T  */
#line 519 "yacc_sql.y"
             {
      (yyval.value) = new Value(AttrType::NULLS, nullptr, 0);
    }
#line 2196 "yacc_sql.cpp"
    break;

  case 57: /* storage_format: %empty  */
#line 525 "yacc_sql.y"
    {
      (yyval.string) = nullptr;
    }
#line 2204 "yacc_sql.cpp"
    break;

  case 58: /* storage_format: STORAGE FORMAT EQ ID  */
#line 529 "yacc_sql.y"
    {
      (yyval.string) = (yyvsp[0].string);
    }
#line 2212 "yacc_sql.cpp"
    break;

  case 59: /* delete_stmt: DELETE FROM ID where  */
#line 536 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DELETE);
      (yyval.sql_node)->deletion.relation_name = (yyvsp[-1].string);
      if ((yyvsp[0].condition_list) != nullptr) {
        (yyval.sql_node)->deletion.conditions.swap(*(yyvsp[0].condition_list));
        delete (yyvsp[0].condition_list);
      }
      free((yyvsp[-1].string));
    }
#line 2226 "yacc_sql.cpp"
    break;

  case 60: /* assignment: ID EQ expression  */
#line 549 "yacc_sql.y"
    {
      (yyval.assignment) = new std::pair<std::string, std::unique_ptr<Expression>>((yyvsp[-2].string), (yyvsp[0].expression));
      free((yyvsp[-2].string));
    }
#line 2235 "yacc_sql.cpp"
    break;

  case 61: /* assignment_list: assignment  */
#line 556 "yacc_sql.y"
               {
      (yyval.assignments) = new std::vector<std::pair<std::string, std::unique_ptr<Expression>>>();
      (yyval.assignments)->emplace_back(std::move(*(yyvsp[0].assignment)));
      delete (yyvsp[0].assignment);
    }
#line 2245 "yacc_sql.cpp"
    break;

  case 62: /* assignment_list: assignment COMMA assignment_list  */
#line 562 "yacc_sql.y"
    {
      if ((yyvsp[0].assignments) != nullptr) {
        (yyval.assignments) = (yyvsp[0].assignments);
      } else {
        (yyval.assignments) = new std::vector<std::pair<std::string, std::unique_ptr<Expression>>>();
      }
      (yyval.assignments)->emplace_back(std::move(*(yyvsp[-2].assignment)));
      delete (yyvsp[-2].assignment);
    }
#line 2259 "yacc_sql.cpp"
    break;

  case 63: /* update_stmt: UPDATE ID SET assignment_list where  */
#line 575 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_UPDATE);
      (yyval.sql_node)->update.relation_name = (yyvsp[-3].string);

      (yyval.sql_node)->update.assignments.swap(*(yyvsp[-1].assignments));
      std::reverse((yyval.sql_node)->update.assignments.begin(), (yyval.sql_node)->update.assignments.end());
      delete (yyvsp[-1].assignments);
      
      if ((yyvsp[0].condition_list) != nullptr) {
        (yyval.sql_node)->update.conditions.swap(*(yyvsp[0].condition_list));
        delete (yyvsp[0].condition_list);
      }
      free((yyvsp[-3].string));
    }
#line 2278 "yacc_sql.cpp"
    break;

  case 64: /* join_node_list: %empty  */
#line 593 "yacc_sql.y"
    {
      (yyval.join_node_list) = nullptr;
    }
#line 2286 "yacc_sql.cpp"
    break;

  case 65: /* join_node_list: COMMA join_node join_node_list  */
#line 597 "yacc_sql.y"
    {
      if ((yyvsp[0].join_node_list) != nullptr) {
        (yyval.join_node_list) = (yyvsp[0].join_node_list);
      } else {
        (yyval.join_node_list) = new std::vector<InnerJoinSqlNode>;
      }
      (yyval.join_node_list)->emplace_back(std::move(*(yyvsp[-1].join_node)));
    }
#line 2299 "yacc_sql.cpp"
    break;

  case 66: /* join_node: ID alias join_list  */
#line 608 "yacc_sql.y"
    {
      if ((yyvsp[0].join_node) != nullptr) {
        (yyval.join_node) = (yyvsp[0].join_node);
      } else {
        (yyval.join_node) = new InnerJoinSqlNode;
      }
      if ((yyvsp[-1].string) != nullptr) {
        (yyval.join_node)->basic_relation.second = (yyvsp[-1].string);
      }
      (yyval.join_node)->basic_relation.first = (yyvsp[-2].string);
      std::reverse((yyval.join_node)->join_relations.begin(), (yyval.join_node)->join_relations.end());
      std::reverse((yyval.join_node)->conditions.begin(), (yyval.join_node)->conditions.end());
      free((yyvsp[-2].string));
    }
#line 2318 "yacc_sql.cpp"
    break;

  case 67: /* join_list: %empty  */
#line 625 "yacc_sql.y"
    {
      (yyval.join_node) =  nullptr;
    }
#line 2326 "yacc_sql.cpp"
    break;

  case 68: /* join_list: INNER JOIN ID alias ON condition_list join_list  */
#line 629 "yacc_sql.y"
    {
      if ((yyvsp[0].join_node) != nullptr) {
        (yyval.join_node) = (yyvsp[0].join_node);
      } else {
        (yyval.join_node) = new InnerJoinSqlNode;
      }
      std::pair<std::string, std::string> join_relation;
      if ((yyvsp[-3].string) != nullptr) {
        join_relation.second = (yyvsp[-3].string);
      }
      join_relation.first = (yyvsp[-4].string);
      (yyval.join_node)->join_relations.emplace_back(join_relation);
      (yyval.join_node)->conditions.emplace_back(std::move(*(yyvsp[-1].condition_list)));
      free((yyvsp[-4].string));
    }
#line 2346 "yacc_sql.cpp"
    break;

  case 69: /* select_stmt: SELECT expression_list FROM join_node join_node_list where order_by group_by  */
#line 647 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SELECT);
      if ((yyvsp[-6].expression_list) != nullptr) {
        (yyval.sql_node)->selection.expressions.swap(*(yyvsp[-6].expression_list));
        delete (yyvsp[-6].expression_list);
      }

      if ((yyvsp[-3].join_node_list) != nullptr) {
        (yyval.sql_node)->selection.relations.swap(*(yyvsp[-3].join_node_list));
        delete (yyvsp[-3].join_node_list);
      }
      (yyval.sql_node)->selection.relations.emplace_back(std::move(*(yyvsp[-4].join_node)));
      std::reverse((yyval.sql_node)->selection.relations.begin(), (yyval.sql_node)->selection.relations.end());

      if ((yyvsp[-2].condition_list) != nullptr) {
        (yyval.sql_node)->selection.conditions.swap(*(yyvsp[-2].condition_list));
        delete (yyvsp[-2].condition_list);
      }

      if ((yyvsp[-1].sort_unit_list) != nullptr) {
        (yyval.sql_node)->selection.order_by.swap(*(yyvsp[-1].sort_unit_list));
        std::reverse((yyval.sql_node)->selection.order_by.begin(), (yyval.sql_node)->selection.order_by.end());
        delete (yyvsp[-1].sort_unit_list);
      }

      if ((yyvsp[0].expression_list) != nullptr) {
        (yyval.sql_node)->selection.group_by.swap(*(yyvsp[0].expression_list));
        delete (yyvsp[0].expression_list);
      }
    }
#line 2381 "yacc_sql.cpp"
    break;

  case 70: /* order_by: %empty  */
#line 681 "yacc_sql.y"
    {
      (yyval.sort_unit_list) = nullptr;
    }
#line 2389 "yacc_sql.cpp"
    break;

  case 71: /* order_by: ORDER BY sort_unit_list  */
#line 685 "yacc_sql.y"
    {
      (yyval.sort_unit_list) = (yyvsp[0].sort_unit_list);
    }
#line 2397 "yacc_sql.cpp"
    break;

  case 72: /* sort_unit_list: sort_unit  */
#line 692 "yacc_sql.y"
    {
      (yyval.sort_unit_list) = new std::vector<OrderBySqlNode>;
      (yyval.sort_unit_list)->emplace_back(std::move(*(yyvsp[0].sort_unit)));
      delete (yyvsp[0].sort_unit);
    }
#line 2407 "yacc_sql.cpp"
    break;

  case 73: /* sort_unit_list: sort_unit COMMA sort_unit_list  */
#line 698 "yacc_sql.y"
    {
      if ((yyvsp[0].sort_unit_list) != nullptr) {
        (yyval.sort_unit_list) = (yyvsp[0].sort_unit_list);
      } else {
        (yyval.sort_unit_list) = new std::vector<OrderBySqlNode>;
      }
      (yyval.sort_unit_list)->emplace_back(std::move(*(yyvsp[-2].sort_unit)));
      delete (yyvsp[-2].sort_unit);
    }
#line 2421 "yacc_sql.cpp"
    break;

  case 74: /* sort_unit: expression  */
#line 711 "yacc_sql.y"
    {
      (yyval.sort_unit) = new OrderBySqlNode;
      (yyval.sort_unit)->expression.reset((yyvsp[0].expression));
      (yyval.sort_unit)->is_asc = true;
    }
#line 2431 "yacc_sql.cpp"
    break;

  case 75: /* sort_unit: expression ASC  */
#line 717 "yacc_sql.y"
    {
      (yyval.sort_unit) = new OrderBySqlNode;
      (yyval.sort_unit)->expression.reset((yyvsp[-1].expression));
      (yyval.sort_unit)->is_asc = true;
    }
#line 2441 "yacc_sql.cpp"
    break;

  case 76: /* sort_unit: expression DESC  */
#line 723 "yacc_sql.y"
    {
      (yyval.sort_unit) = new OrderBySqlNode;
      (yyval.sort_unit)->expression.reset((yyvsp[-1].expression));
      (yyval.sort_unit)->is_asc = false;
    }
#line 2451 "yacc_sql.cpp"
    break;

  case 77: /* calc_stmt: CALC expression_list  */
#line 732 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CALC);
      (yyval.sql_node)->calc.expressions.swap(*(yyvsp[0].expression_list));
      delete (yyvsp[0].expression_list);
    }
#line 2461 "yacc_sql.cpp"
    break;

  case 78: /* alias: %empty  */
#line 741 "yacc_sql.y"
    {
      (yyval.string) = nullptr;
    }
#line 2469 "yacc_sql.cpp"
    break;

  case 79: /* alias: ID  */
#line 745 "yacc_sql.y"
    {
      (yyval.string) = (yyvsp[0].string);
    }
#line 2477 "yacc_sql.cpp"
    break;

  case 80: /* alias: AS ID  */
#line 748 "yacc_sql.y"
            {
      (yyval.string) = (yyvsp[0].string);
    }
#line 2485 "yacc_sql.cpp"
    break;

  case 81: /* expression_list: %empty  */
#line 755 "yacc_sql.y"
    {
      (yyval.expression_list) = nullptr;
    }
#line 2493 "yacc_sql.cpp"
    break;

  case 82: /* expression_list: expression alias  */
#line 759 "yacc_sql.y"
    {
      if ((yyvsp[0].string) != nullptr) {
        (yyvsp[-1].expression)->set_alias(std::string((yyvsp[0].string)));
      }
      (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      (yyval.expression_list)->emplace_back((yyvsp[-1].expression));
    }
#line 2505 "yacc_sql.cpp"
    break;

  case 83: /* expression_list: expression alias COMMA expression_list  */
#line 767 "yacc_sql.y"
    {
      if ((yyvsp[-2].string) != nullptr) {
        (yyvsp[-3].expression)->set_alias(std::string((yyvsp[-2].string)));
      }
      if ((yyvsp[0].expression_list) != nullptr) {
        (yyval.expression_list) = (yyvsp[0].expression_list);
      } else {
        (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      }
      (yyval.expression_list)->emplace((yyval.expression_list)->begin(), (yyvsp[-3].expression));
    }
#line 2521 "yacc_sql.cpp"
    break;

  case 84: /* expression: expression '+' expression  */
#line 780 "yacc_sql.y"
                              {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::ADD, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2529 "yacc_sql.cpp"
    break;

  case 85: /* expression: expression '-' expression  */
#line 783 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::SUB, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2537 "yacc_sql.cpp"
    break;

  case 86: /* expression: expression '*' expression  */
#line 786 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::MUL, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));;
    }
#line 2545 "yacc_sql.cpp"
    break;

  case 87: /* expression: expression '/' expression  */
#line 789 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::DIV, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2553 "yacc_sql.cpp"
    break;

  case 88: /* expression: LBRACE expression_list RBRACE  */
#line 792 "yacc_sql.y"
                                    {
      if ((yyvsp[-1].expression_list)->size() == 1) {
        (yyval.expression) = (yyvsp[-1].expression_list)->at(0).get();
      } else {
        (yyval.expression) = new ExprListExpr(std::move(*(yyvsp[-1].expression_list)));
      }
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
    }
#line 2566 "yacc_sql.cpp"
    break;

  case 89: /* expression: '-' expression  */
#line 800 "yacc_sql.y"
                                  { // 此处用于匹配取反运算
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::NEGATIVE, (yyvsp[0].expression), nullptr, sql_string, &(yyloc));
    }
#line 2574 "yacc_sql.cpp"
    break;

  case 90: /* expression: value  */
#line 803 "yacc_sql.y"
            {
      (yyval.expression) = new ValueExpr(*(yyvsp[0].value));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[0].value);
    }
#line 2584 "yacc_sql.cpp"
    break;

  case 91: /* expression: rel_attr  */
#line 808 "yacc_sql.y"
               {
      RelAttrSqlNode *node = (yyvsp[0].rel_attr);
      (yyval.expression) = new UnboundFieldExpr(node->relation_name, node->attribute_name);
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[0].rel_attr);
    }
#line 2595 "yacc_sql.cpp"
    break;

  case 92: /* expression: '*'  */
#line 814 "yacc_sql.y"
          {
      (yyval.expression) = new StarExpr();
    }
#line 2603 "yacc_sql.cpp"
    break;

  case 93: /* expression: ID DOT '*'  */
#line 817 "yacc_sql.y"
                 {
      (yyval.expression) = new StarExpr((yyvsp[-2].string));
      free((yyvsp[-2].string));
    }
#line 2612 "yacc_sql.cpp"
    break;

  case 94: /* expression: aggregation_func  */
#line 821 "yacc_sql.y"
                       {
      (yyval.expression) = (yyvsp[0].expression);
    }
#line 2620 "yacc_sql.cpp"
    break;

  case 95: /* expression: vector_func  */
#line 824 "yacc_sql.y"
                  {
      (yyval.expression) = (yyvsp[0].expression);
    }
#line 2628 "yacc_sql.cpp"
    break;

  case 96: /* expression: LBRACE select_stmt RBRACE  */
#line 827 "yacc_sql.y"
                                {
      (yyval.expression) = new SubQueryExpr(make_unique<ParsedSqlNode>(std::move(*(yyvsp[-1].sql_node))));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
    }
#line 2637 "yacc_sql.cpp"
    break;

  case 97: /* aggregation_func: aggregation_name LBRACE expression_list RBRACE  */
#line 833 "yacc_sql.y"
                                                   {
      if ((yyvsp[-1].expression_list) == nullptr || (yyvsp[-1].expression_list)->size() != 1) {
        Expression *none_expr = new NoneExpr();
        (yyval.expression) = new UnboundAggregateExpr((yyvsp[-3].string), none_expr);
      } else {
        (yyval.expression) = create_aggregate_expression((yyvsp[-3].string), (yyvsp[-1].expression_list)->at(0).get(), sql_string, &(yyloc));
      }
    }
#line 2650 "yacc_sql.cpp"
    break;

  case 98: /* aggregation_name: COUNT  */
#line 844 "yacc_sql.y"
          { (yyval.string) = (char *)"COUNT"; }
#line 2656 "yacc_sql.cpp"
    break;

  case 99: /* aggregation_name: SUM  */
#line 845 "yacc_sql.y"
          { (yyval.string) = (char *)"SUM"; }
#line 2662 "yacc_sql.cpp"
    break;

  case 100: /* aggregation_name: MAX  */
#line 846 "yacc_sql.y"
          { (yyval.string) = (char *)"MAX"; }
#line 2668 "yacc_sql.cpp"
    break;

  case 101: /* aggregation_name: MIN  */
#line 847 "yacc_sql.y"
          { (yyval.string) = (char *)"MIN"; }
#line 2674 "yacc_sql.cpp"
    break;

  case 102: /* aggregation_name: AVG  */
#line 848 "yacc_sql.y"
          { (yyval.string) = (char *)"AVG"; }
#line 2680 "yacc_sql.cpp"
    break;

  case 103: /* vector_func: vector_func_name LBRACE expression COMMA expression RBRACE  */
#line 852 "yacc_sql.y"
                                                               {
      (yyval.expression) = create_vector_expression((yyvsp[-5].string), (yyvsp[-3].expression), (yyvsp[-1].expression), sql_string, &(yyloc));
    }
#line 2688 "yacc_sql.cpp"
    break;

  case 104: /* vector_func_name: L2_DISTANCE  */
#line 857 "yacc_sql.y"
                      { (yyval.string) = (char *)"L2_DISTANCE"; }
#line 2694 "yacc_sql.cpp"
    break;

  case 105: /* vector_func_name: COSINE_DISTANCE  */
#line 858 "yacc_sql.y"
                      { (yyval.string) = (char *)"COSINE_DISTANCE"; }
#line 2700 "yacc_sql.cpp"
    break;

  case 106: /* vector_func_name: INNER_PRODUCT  */
#line 859 "yacc_sql.y"
                      { (yyval.string) = (char *)"INNER_PRODUCT"; }
#line 2706 "yacc_sql.cpp"
    break;

  case 107: /* rel_attr: ID  */
#line 863 "yacc_sql.y"
       {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 2716 "yacc_sql.cpp"
    break;

  case 108: /* rel_attr: ID DOT ID  */
#line 868 "yacc_sql.y"
                {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->relation_name  = (yyvsp[-2].string);
      (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 2728 "yacc_sql.cpp"
    break;

  case 109: /* where: %empty  */
#line 879 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 2736 "yacc_sql.cpp"
    break;

  case 110: /* where: WHERE condition_list  */
#line 882 "yacc_sql.y"
                           {
      (yyval.condition_list) = new std::vector<ConditionSqlNode>;
      (yyval.condition_list)->swap(*(yyvsp[0].condition_list));  
    }
#line 2745 "yacc_sql.cpp"
    break;

  case 111: /* condition_list: %empty  */
#line 889 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 2753 "yacc_sql.cpp"
    break;

  case 112: /* condition_list: condition  */
#line 892 "yacc_sql.y"
                {
      (yyval.condition_list) = new std::vector<ConditionSqlNode>;
      (yyval.condition_list)->emplace_back(std::move(*(yyvsp[0].condition)));
      delete (yyvsp[0].condition);
    }
#line 2763 "yacc_sql.cpp"
    break;

  case 113: /* condition_list: condition AND condition_list  */
#line 897 "yacc_sql.y"
                                   {
      (yyval.condition_list) = (yyvsp[0].condition_list);
      (yyval.condition_list)->emplace_back(std::move(*(yyvsp[-2].condition)));
      delete (yyvsp[-2].condition);
    }
#line 2773 "yacc_sql.cpp"
    break;

  case 114: /* condition: expression comp_op expression  */
#line 905 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)-> left_expression.reset((yyvsp[-2].expression));
      (yyval.condition)->right_expression.reset((yyvsp[0].expression));
      (yyval.condition)->comp = (yyvsp[-1].comp);
      LOG_DEBUG("condition: %s | %s", (yyvsp[-2].expression)->name(),  (yyvsp[0].expression)->name());
    }
#line 2785 "yacc_sql.cpp"
    break;

  case 115: /* condition: EXISTS expression  */
#line 912 "yacc_sql.y"
                        {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_expression.reset((yyvsp[0].expression));

      Value value;
      value.set_type(AttrType::NULLS);
      (yyval.condition)->right_expression.reset(new ValueExpr(value));

      (yyval.condition)->comp = EXISTS_COMP;
    }
#line 2800 "yacc_sql.cpp"
    break;

  case 116: /* condition: NOT EXISTS expression  */
#line 922 "yacc_sql.y"
                            {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_expression.reset((yyvsp[0].expression));

      Value value;
      value.set_type(AttrType::NULLS);
      (yyval.condition)->right_expression.reset(new ValueExpr(value));

      (yyval.condition)->comp = NOT_EXISTS_COMP;
    }
#line 2815 "yacc_sql.cpp"
    break;

  case 117: /* comp_op: EQ  */
#line 935 "yacc_sql.y"
               { (yyval.comp) = EQUAL_TO;          }
#line 2821 "yacc_sql.cpp"
    break;

  case 118: /* comp_op: LT  */
#line 936 "yacc_sql.y"
               { (yyval.comp) = LESS_THAN;         }
#line 2827 "yacc_sql.cpp"
    break;

  case 119: /* comp_op: GT  */
#line 937 "yacc_sql.y"
               { (yyval.comp) = GREAT_THAN;        }
#line 2833 "yacc_sql.cpp"
    break;

  case 120: /* comp_op: LE  */
#line 938 "yacc_sql.y"
               { (yyval.comp) = LESS_EQUAL;        }
#line 2839 "yacc_sql.cpp"
    break;

  case 121: /* comp_op: GE  */
#line 939 "yacc_sql.y"
               { (yyval.comp) = GREAT_EQUAL;       }
#line 2845 "yacc_sql.cpp"
    break;

  case 122: /* comp_op: NE  */
#line 940 "yacc_sql.y"
               { (yyval.comp) = NOT_EQUAL;         }
#line 2851 "yacc_sql.cpp"
    break;

  case 123: /* comp_op: LIKE  */
#line 941 "yacc_sql.y"
               { (yyval.comp) = LIKE_COMP;         }
#line 2857 "yacc_sql.cpp"
    break;

  case 124: /* comp_op: NOT LIKE  */
#line 942 "yacc_sql.y"
               { (yyval.comp) = NOT_LIKE_COMP;     }
#line 2863 "yacc_sql.cpp"
    break;

  case 125: /* comp_op: IS  */
#line 943 "yacc_sql.y"
               { (yyval.comp) = IS_COMP;           }
#line 2869 "yacc_sql.cpp"
    break;

  case 126: /* comp_op: IS NOT  */
#line 944 "yacc_sql.y"
               { (yyval.comp) = IS_NOT_COMP;       }
#line 2875 "yacc_sql.cpp"
    break;

  case 127: /* comp_op: IN  */
#line 945 "yacc_sql.y"
               { (yyval.comp) = IN_COMP;           }
#line 2881 "yacc_sql.cpp"
    break;

  case 128: /* comp_op: NOT IN  */
#line 946 "yacc_sql.y"
               { (yyval.comp) = NOT_IN_COMP;       }
#line 2887 "yacc_sql.cpp"
    break;

  case 129: /* comp_op: EXISTS  */
#line 947 "yacc_sql.y"
               { (yyval.comp) = EXISTS_COMP;       }
#line 2893 "yacc_sql.cpp"
    break;

  case 130: /* comp_op: NOT EXISTS  */
#line 948 "yacc_sql.y"
                 { (yyval.comp) = NOT_EXISTS_COMP; }
#line 2899 "yacc_sql.cpp"
    break;

  case 131: /* group_by: %empty  */
#line 954 "yacc_sql.y"
    {
      (yyval.expression_list) = nullptr;
    }
#line 2907 "yacc_sql.cpp"
    break;

  case 132: /* load_data_stmt: LOAD DATA INFILE SSS INTO TABLE ID  */
#line 960 "yacc_sql.y"
    {
      char *tmp_file_name = common::substr((yyvsp[-3].string), 1, strlen((yyvsp[-3].string)) - 2);
      
      (yyval.sql_node) = new ParsedSqlNode(SCF_LOAD_DATA);
      (yyval.sql_node)->load_data.relation_name = (yyvsp[0].string);
      (yyval.sql_node)->load_data.file_name = tmp_file_name;
      free((yyvsp[0].string));
      free(tmp_file_name);
    }
#line 2921 "yacc_sql.cpp"
    break;

  case 133: /* explain_stmt: EXPLAIN command_wrapper  */
#line 973 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXPLAIN);
      (yyval.sql_node)->explain.sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[0].sql_node));
    }
#line 2930 "yacc_sql.cpp"
    break;

  case 134: /* set_variable_stmt: SET ID EQ value  */
#line 981 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SET_VARIABLE);
      (yyval.sql_node)->set_variable.name  = (yyvsp[-2].string);
      (yyval.sql_node)->set_variable.value = *(yyvsp[0].value);
      free((yyvsp[-2].string));
      delete (yyvsp[0].value);
    }
#line 2942 "yacc_sql.cpp"
    break;


#line 2946 "yacc_sql.cpp"

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
  *++yylsp = yyloc;

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
      {
        yypcontext_t yyctx
          = {yyssp, yytoken, &yylloc};
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == -1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *,
                             YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (yymsg)
              {
                yysyntax_error_status
                  = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
                yymsgp = yymsg;
              }
            else
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = YYENOMEM;
              }
          }
        yyerror (&yylloc, sql_string, sql_result, scanner, yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          YYNOMEM;
      }
    }

  yyerror_range[1] = yylloc;
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
                      yytoken, &yylval, &yylloc, sql_string, sql_result, scanner);
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

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, yylsp, sql_string, sql_result, scanner);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  ++yylsp;
  YYLLOC_DEFAULT (*yylsp, yyerror_range, 2);

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
  yyerror (&yylloc, sql_string, sql_result, scanner, YY_("memory exhausted"));
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
                  yytoken, &yylval, &yylloc, sql_string, sql_result, scanner);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, yylsp, sql_string, sql_result, scanner);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
  return yyresult;
}

#line 993 "yacc_sql.y"

//_____________________________________________________________________
extern void scan_string(const char *str, yyscan_t scanner);

int sql_parse(const char *s, ParsedSqlResult *sql_result) {
  yyscan_t scanner;
  yylex_init(&scanner);
  scan_string(s, scanner);
  int result = yyparse(s, sql_result, scanner);
  yylex_destroy(scanner);
  return result;
}
