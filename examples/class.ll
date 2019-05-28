def maullar(){
	print "Meowww"
}

def ladrar(){
	print "Woof!"
}

def Gato(nombre){
	g = nombre
	g.nombre = nombre
	g.sonido = maullar
	return g
}

def Perro(nombre){
	p = nombre
	p.nombre = nombre
	p.sonido = ladrar
	return p
}

def Mascota(tipo,nombre){
	if tipo=="Perro"{
		return Perro(nombre)
	}
	if(tipo=="Gato"){
		return Gato(nombre)
	}
	print "Tipo de animal no valido!"
	exit()
}

g = Mascota("Gato","g1")
g.sonido()
g.nombre
p = Mascota("Perro","p1")
p.sonido()
p.nombre
n = Mascota("Leon","L1")

