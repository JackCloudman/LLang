def crearNodo(objeto,tipo){
  a = objeto
  a.tipo = tipo
  a.izquierda = None
  a.derecha = None
  return a
}

def insertarIzquierda(nodo,objeto,tipo){
   n = crearNodo(objeto,tipo)
   nodo.izquierda = n
   return n
}

def insertarDerecha(nodo,objeto,tipo){
   n = crearNodo(objeto,tipo)
   nodo.derecha = n
   return n
}

def Mostrar(nodo){
  if(not nodo){
    return
  }

  Mostrar(nodo.izquierda)
  print nodo
  Mostrar(nodo.derecha)
}

def nuevoAnimal(){
  p = crearNodo(input("No encontre el animal del que hablas, porfavor ingresa una nueva pregunta que lo identifique: "),"pregunta")
  a = None
  while(a==None){
    a = input("Nombre del animal: ")
    if not a{
      a = None
    }else{
      i = insertarIzquierda(p,a,"animal")
    }
  }
  return p
}

a = crearNodo("¿Tu animal es un Mamifero? ","pregunta")
n1 = insertarIzquierda(a,"¿Es domestico? ","pregunta")
n2 = insertarIzquierda(n1,"¿Es un felino? ","pregunta")
an = insertarIzquierda(n2,"Gato","animal")
an = insertarDerecha(n2,"Perro","animal")
n2 = insertarDerecha(n1,"¿Es un felino? ","pregunta")
an = insertarIzquierda(n2,"Tigre","animal")
an = insertarDerecha(n2,"Lobo","animal")

n1 = insertarDerecha(a,"¿Es domestico? ","pregunta")
n2 = insertarIzquierda(n1,"¿Es acuatico? ","pregunta")
an = insertarIzquierda(n2,"Pez","animal")
an = insertarDerecha(n2,"Tortuga","animal")
n2 = insertarDerecha(n1,"¿Es acuatico? ","pregunta")
an = insertarIzquierda(n2,"Tiburon","animal")
an = insertarDerecha(n2,"Serpiente","animal")

aux1 = aux2 = a
r2 = ""
bandera = True
while(bandera){
  if(aux1.tipo == "pregunta"){
    r = input(aux1)
    aux2 = aux1
    r2 = r
    if r=="si"{
      if not aux1.izquierda{
        p = nuevoAnimal()
        aux1.izquierda = p
      }else{
        aux1 = aux1.izquierda
      }
    }else{
      if not aux1.derecha{
        p = nuevoAnimal()
        aux1.derecha = p
      }else{
        aux1 = aux1.derecha
      }
    }
  }else{
    r = input("¿Tu animal es: "+aux1+"? ")
    if(r=="si"){
      print "Lo sabia!"
      bandera = False
    }else{
      p = nuevoAnimal()
      p.derecha = aux1
      if(r2=="si"){
        aux2.izquierda = p
      }else{
        aux2.derecha = p
      }
      aux1 = aux2 = a
    }
  }
}

