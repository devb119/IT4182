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
  // DONE
  Scope* scope = symtab->currentScope;
  Object* obj;
  while (scope)
  {
    obj = findObject(scope->objList, name);
    if(obj) return obj;
    scope = scope->outer;
  }
  obj = findObject(symtab->globalObjectList, name);
  if(obj) return obj;
  return NULL;
  
}

void checkFreshIdent(char *name) {
  // DONE
  Object* obj = findObject(symtab->currentScope->objList, name);
  // if there is an object already existed in current scope -> error
  if(obj) return error(ERR_DUPLICATE_IDENT, currentToken->lineNo, currentToken->colNo);
}

Object* checkDeclaredIdent(char* name) {
  // DONE
  Object* obj = lookupObject(name);
  if(!obj) error(ERR_UNDECLARED_IDENT, currentToken->lineNo, currentToken->colNo);
  return obj;
}

Object* checkDeclaredConstant(char* name) {
  // DONE
  Object* obj = lookupObject(name);
  if(!obj) 
  error(ERR_UNDECLARED_CONSTANT, currentToken->lineNo, currentToken->colNo);
  if(obj->kind != OBJ_CONSTANT) 
  error(ERR_INVALID_CONSTANT, currentToken->lineNo, currentToken->colNo);
  return obj;
}

Object* checkDeclaredType(char* name) {
  // DONE
  Object *obj = lookupObject(name);
  if(!obj) 
  error(ERR_UNDECLARED_TYPE, currentToken->lineNo, currentToken->colNo);
  if(obj->kind != OBJ_TYPE)
  error(ERR_INVALID_TYPE, currentToken->lineNo, currentToken->colNo);
  return obj;
}

Object* checkDeclaredVariable(char* name) {
  // DONE
  Object* obj = lookupObject(name);
  if(!obj) 
  error(ERR_UNDECLARED_VARIABLE, currentToken->lineNo, currentToken->colNo);
  if(obj->kind != OBJ_VARIABLE)
  error(ERR_INVALID_VARIABLE, currentToken->lineNo, currentToken->colNo);

  return obj;
}

Object* checkDeclaredFunction(char* name) {
  // DONE
  Object* obj = lookupObject(name);
  if(!obj)
  error(ERR_UNDECLARED_FUNCTION, currentToken->lineNo, currentToken->colNo);
  if(obj->kind != OBJ_FUNCTION)
  error(ERR_INVALID_FUNCTION, currentToken->lineNo, currentToken->colNo);

  return obj;
}

Object* checkDeclaredProcedure(char* name) {
  // DONE
  Object* obj = lookupObject(name);
  if(!obj)
  error(ERR_UNDECLARED_PROCEDURE, currentToken->lineNo, currentToken->colNo);
  if(obj->kind != OBJ_PROCEDURE)
  error(ERR_UNDECLARED_PROCEDURE, currentToken->lineNo, currentToken->colNo);

  return obj;
}

Object* checkDeclaredLValueIdent(char* name) {
  // TODO
}

