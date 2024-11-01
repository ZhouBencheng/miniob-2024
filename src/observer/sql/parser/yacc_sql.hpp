/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_YACC_SQL_HPP_INCLUDED
# define YY_YY_YACC_SQL_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    SEMICOLON = 258,               /* SEMICOLON  */
    BY = 259,                      /* BY  */
    CREATE = 260,                  /* CREATE  */
    DROP = 261,                    /* DROP  */
    GROUP = 262,                   /* GROUP  */
    TABLE = 263,                   /* TABLE  */
    TABLES = 264,                  /* TABLES  */
    INDEX = 265,                   /* INDEX  */
    CALC = 266,                    /* CALC  */
    SELECT = 267,                  /* SELECT  */
    COUNT = 268,                   /* COUNT  */
    SUM = 269,                     /* SUM  */
    MAX = 270,                     /* MAX  */
    MIN = 271,                     /* MIN  */
    AVG = 272,                     /* AVG  */
    L2_DISTANCE = 273,             /* L2_DISTANCE  */
    COSINE_DISTANCE = 274,         /* COSINE_DISTANCE  */
    INNER_PRODUCT = 275,           /* INNER_PRODUCT  */
    DESC = 276,                    /* DESC  */
    SHOW = 277,                    /* SHOW  */
    SYNC = 278,                    /* SYNC  */
    INSERT = 279,                  /* INSERT  */
    DELETE = 280,                  /* DELETE  */
    UPDATE = 281,                  /* UPDATE  */
    LBRACE = 282,                  /* LBRACE  */
    RBRACE = 283,                  /* RBRACE  */
    COMMA = 284,                   /* COMMA  */
    TRX_BEGIN = 285,               /* TRX_BEGIN  */
    TRX_COMMIT = 286,              /* TRX_COMMIT  */
    TRX_ROLLBACK = 287,            /* TRX_ROLLBACK  */
    INT_T = 288,                   /* INT_T  */
    STRING_T = 289,                /* STRING_T  */
    FLOAT_T = 290,                 /* FLOAT_T  */
    VECTOR_T = 291,                /* VECTOR_T  */
    DATE_T = 292,                  /* DATE_T  */
    HELP = 293,                    /* HELP  */
    EXIT = 294,                    /* EXIT  */
    DOT = 295,                     /* DOT  */
    INTO = 296,                    /* INTO  */
    VALUES = 297,                  /* VALUES  */
    FROM = 298,                    /* FROM  */
    WHERE = 299,                   /* WHERE  */
    AND = 300,                     /* AND  */
    SET = 301,                     /* SET  */
    INNER = 302,                   /* INNER  */
    JOIN = 303,                    /* JOIN  */
    ON = 304,                      /* ON  */
    LOAD = 305,                    /* LOAD  */
    DATA = 306,                    /* DATA  */
    INFILE = 307,                  /* INFILE  */
    EXPLAIN = 308,                 /* EXPLAIN  */
    STORAGE = 309,                 /* STORAGE  */
    FORMAT = 310,                  /* FORMAT  */
    EQ = 311,                      /* EQ  */
    LT = 312,                      /* LT  */
    GT = 313,                      /* GT  */
    LE = 314,                      /* LE  */
    GE = 315,                      /* GE  */
    NE = 316,                      /* NE  */
    NOT = 317,                     /* NOT  */
    IS = 318,                      /* IS  */
    IN = 319,                      /* IN  */
    EXISTS = 320,                  /* EXISTS  */
    NULL_T = 321,                  /* NULL_T  */
    LIKE = 322,                    /* LIKE  */
    UNIQUE = 323,                  /* UNIQUE  */
    NUMBER = 324,                  /* NUMBER  */
    FLOAT = 325,                   /* FLOAT  */
    ID = 326,                      /* ID  */
    SSS = 327,                     /* SSS  */
    LOWEST = 328,                  /* LOWEST  */
    UMINUS = 329                   /* UMINUS  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 147 "yacc_sql.y"

  ParsedSqlNode *                            sql_node;
  ConditionSqlNode *                         condition;
  InnerJoinSqlNode *                         join_node;
  Value *                                    value;
  enum CompOp                                comp;
  RelAttrSqlNode *                           rel_attr;
  std::vector<AttrInfoSqlNode> *             attr_infos;
  AttrInfoSqlNode *                          attr_info;
  Expression *                               expression;
  std::vector<std::unique_ptr<Expression>> * expression_list;
  std::vector<Value> *                       value_list;
  std::vector<ConditionSqlNode> *            condition_list;
  std::vector<InnerJoinSqlNode> *            join_node_list;
  std::vector<RelAttrSqlNode> *              rel_attr_list;
  std::vector<std::string> *                 relation_list;
  char *                                     string;
  int                                        number;
  float                                      floats;
  bool                                       boolean;

#line 160 "yacc_sql.hpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif




int yyparse (const char * sql_string, ParsedSqlResult * sql_result, void * scanner);


#endif /* !YY_YY_YACC_SQL_HPP_INCLUDED  */
