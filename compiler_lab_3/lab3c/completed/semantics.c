/* 
 * @copyright (c) 2008, Hedspi, Hanoi University of Technology
 * @author Huu-Duc Nguyen
 * @version 1.0
 */

#include <stdlib.h>
#include <string.h>
#include "semantics.h"
#include "error.h"

extern SymTab* symtab;
extern Token* currentToken;

Object* lookupObject(char *name) {
  // NEW
  Scope *sc = symtab->currentScope;
  Object *obj;

  while (sc != NULL){
    obj = findObject(sc->objList, name);
    if (obj != NULL) return obj;
    sc = sc->outer;
  }
  obj = findObject(symtab->globalObjectList, name);
  if (obj != NULL) return obj;
  else return NULL;
}

void checkFreshIdent(char *name) {
  // NEW
  if (findObject(symtab->currentScope->objList, name) != NULL)
    error(ERR_DUPLICATE_IDENT, currentToken->lineNo, currentToken->colNo);
}

Object* checkDeclaredIdent(char* name) {
  // NEW
  Object *obj = lookupObject(name);
  if (obj == NULL) error(ERR_UNDECLARED_IDENT, currentToken->lineNo, currentToken->colNo);
  return obj;
}

Object* checkDeclaredConstant(char* name) {
  // NEW
  int clino = currentToken->lineNo;
  int ccono = currentToken->colNo;
  Object *obj = lookupObject(name);

  if (obj == NULL) error(ERR_UNDECLARED_CONSTANT, clino, ccono);
  if (obj->kind != OBJ_CONSTANT) error(ERR_INVALID_CONSTANT, clino, ccono);
  return obj;
}

Object* checkDeclaredType(char* name) {
  // NEW
  int clino = currentToken->lineNo;
  int ccono = currentToken->colNo;
  Object *obj = lookupObject(name);

  if (obj == NULL) error(ERR_UNDECLARED_TYPE, clino, ccono);
  if (obj->kind != OBJ_TYPE) error(ERR_INVALID_TYPE, clino, ccono);
  return obj;
}

Object* checkDeclaredVariable(char* name) {
  // NEW
  int clino = currentToken->lineNo;
  int ccono = currentToken->colNo;
  Object *obj = lookupObject(name);

  if (obj == NULL) error(ERR_UNDECLARED_VARIABLE, clino, ccono);
  if (obj->kind != OBJ_VARIABLE) error(ERR_INVALID_VARIABLE, clino, ccono);
  return obj;
}

Object* checkDeclaredFunction(char* name) {
  // NEW
  int clino = currentToken->lineNo;
  int ccono = currentToken->colNo;
  Object *obj = lookupObject(name);

  if (obj == NULL) error(ERR_UNDECLARED_FUNCTION, clino, ccono);
  if (obj->kind != OBJ_FUNCTION) error(ERR_INVALID_FUNCTION, clino, ccono);
  return obj;
}

Object* checkDeclaredProcedure(char* name) {
  // NEW
  int clino = currentToken->lineNo;
  int ccono = currentToken->colNo;
  Object *obj = lookupObject(name);

  if (obj == NULL) error(ERR_UNDECLARED_PROCEDURE, clino, ccono);
  if (obj->kind != OBJ_PROCEDURE) error(ERR_INVALID_PROCEDURE, clino, ccono);
  return obj;
}

Object* checkDeclaredLValueIdent(char* name) {
  // NEW
  int clino = currentToken->lineNo;
  int ccono = currentToken->colNo;
  Object *obj = lookupObject(name);

  if (obj == NULL) error(ERR_UNDECLARED_IDENT, clino, ccono);

  switch (obj->kind){
    case OBJ_VARIABLE:
    case OBJ_PARAMETER:
      break;

    case OBJ_FUNCTION:
      if (obj != symtab->currentScope->owner) error(ERR_INVALID_IDENT, clino, ccono);
      break;

    default:
      error(ERR_INVALID_IDENT, clino, ccono);
  }
  return obj;
}

