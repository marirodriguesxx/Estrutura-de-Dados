/*
TAD MyVec
- Representa uma lista implementada por contiguidade
- Interface similar a da classe Vector do STL
- Criado por Salles Magalhaes em 19/02/2018

*/

#ifndef MyVec_H__
#define MyVec_H__

#include <iostream>
#include <string>
#include <ostream>


//Excessao usada pela classe MyVec
class MyVecException {
private:
	std::string msg;
public:
	MyVecException (const std::string &msg0): msg(msg0) { }
	const std::string & what() const { return msg; }
};


template<class T>
class MyVec {
public:
	template<class T2>
	friend std::ostream& operator<<(std::ostream &, const MyVec<T2> &);

	//construtores/destrutures/etc
	MyVec();
	MyVec(int n, const T&init=T());

	//destrutor
	~MyVec() { destroy(); };

	//Construtor de copia
	MyVec(const MyVec &);
	MyVec & operator=(const MyVec &);

	//funcoes de acesso
	T &operator[](int pos) {return data[pos];}
	const T &operator[](int pos) const {return data[pos];}
	void push_back(const T&);
	void resize(int newSize);
	void insert(const T&,int pos);  
	void clear();

	void empty() const {return size() == 0;};
	int size() const {return dataSize;};

	int eraseMatchingElements(const T &elem); // ok
	void sortedInsert(const T &elem);  //ok



private:
	T* data;            //declare o membro de dados data, que devera armazenar os elementos da lista
	int dataSize;      //quantos elementos ha na lista?
	int dataCapacity; //quantos elementos atualmente cabem na lista? 

	void create();
	void destroy();
	void resizeCapacity(int newCapacity);
};


// Ordem de complexidade : O(n). Acredito que não há como ser mais otimizada
// o cont será um indicador de que há elementos repetidos, uma vez que o cont é incrementado, todas as posiçoes posteriores serão preenchidas 
//em uma posição anterior, fazendo com que o elemento repetido seja sobrescrito
template<class T>
int MyVec<T>::eraseMatchingElements(const T &elem){
	int cont = 0;
	for(int i=0; i<dataSize; i++){
		if(data[i]==elem)				//se o elemento recebido é igual a algum do vetor
			cont++;						// incrementamos o cont
		
		else{
			data[i-cont] = data[i];		//se o elemento recebido não for igual a posição 
		}
		
	}
	dataSize=dataSize- cont;

	return cont;
}

// ordem de complexidade para o melhor caso: O(n) = ele estar no final do vetor, pois n chamará a inser dentro do for
// ordem de complexidade para o pior caso: O(n^2)
template<class T>
void MyVec<T>::sortedInsert(const T &elem){

	for(int i=0; i<dataSize; i++){	
		if(data[i] > elem){			// se o elemento na posição i é maior que o elemento recebido, inserimos ele
			insert(elem,i);
			return;
		}
	}
	insert(elem,dataSize);      //se n for maior que nenhum dos que ja estao no vetor, inserimos no final
}

template<class T>
void MyVec<T>::push_back(const T&elem) {
	if(dataSize==dataCapacity) {						
		if(dataCapacity==0)					
			resizeCapacity(1);						//aumentamos a capacidade para 1, pois era um vetor vazio antes
		else
			resizeCapacity(2*dataCapacity);
		}
	data[dataSize] = elem;						//adicionamos o elemento na ultima posição
	dataSize++;									//incrementamos o numero de elementos, pois acabamos de adicionar mais um elemento
}

template<class T>
void MyVec<T>::resize(int newSize) {
	if(newSize >= dataCapacity) { 	//primeiro temos que realocar o vector...
		resizeCapacity(newSize); 	//para o resize vamos usar o tamanho exato caso seja necessario realocar o vector..
	}
	for(int i=dataSize;i<newSize;i++) { //preencha a parte "extra" do vector com valores "em branco"
		data[i] = T();
	}
	dataSize = newSize;
}

//insere o elemento na posicao pos e move os elementos ja presentes no vetor
// pos pode ser:
//   uma posicao apos o final do vetor (para inserir na ultima posicao) 
//   ou uma posicao ja existente (nesse caso os elementos nessa posicao e apos ela serao movidos "para a frente")
template<class T>
void MyVec<T>::insert(const T&elem,int pos) {
	if(pos > dataSize || pos < 0) {				// nao pode inserir mais elementos que a capacidade
		throw MyVecException("Erro na funcao insert: posicao invalida");
	}

	if(dataSize == dataCapacity) {       //preciso redimensionar? 
		if(dataCapacity ==0)            //Exercicio: Por que e' preciso testar isso? porque se tiver capacidade zero não é possível inreir
			resizeCapacity(1);
		else
			resizeCapacity(dataCapacity*2);
	}	

	for(int i=dataSize;i>pos;i--)			// percorrendo de trás pra frente o vetor, até chegar na posição que o elemento será inserido
		data[i] = data[i-1];				//"puxando" os elementos para o final do vetor
	data[pos] = elem;
	dataSize++;
}

template<class T>
void MyVec<T>::clear() {
	destroy();
	create();
}

template<class T>
void MyVec<T>::resizeCapacity(int capacidade) {
	if(capacidade<=dataCapacity)				// se a nova capacidade for menor ou igual a antiga, não ha necessidade de fazer resize
		return; 

	T* aux = data;							     
	data = new T[capacidade];					// alocamos o vetor com a nova capacidade

	for(int i=0;i<dataSize;i++)
		data[i] = aux[i];						// resgatando os valores salvos em aux

	delete []aux;	

	dataCapacity = capacidade;					// mudamos a capacidade
}

template<class T>
void MyVec<T>::destroy() {
	delete []data;
	dataSize = dataCapacity = 0;
}

template<class T>
void MyVec<T>::create() {
	data = NULL;
	dataSize = dataCapacity = 0;
}

template<class T>
MyVec<T>::MyVec() {
	create();
}

template<class T>
MyVec<T>::MyVec(int n, const T&init) {
	dataSize = dataCapacity = n;
	data = new T[n];
	for(int i=0;i<n;i++) 
		data[i] = init;
}


//Construtor de copia
template<class T>
MyVec<T>::MyVec(const MyVec &other) {
	create();
	data = NULL;					//inicializando com vazio os elementos
	*this = other;					// utiliza o operador de atribuição, fazendo com que o objeto apontado por this seja other
}

template<class T>
MyVec<T> & MyVec<T>::operator=(const MyVec &other){
	if(this==&other) return *this; // testando autoatribuição 
		destroy(); //Exercicio: por que precisamos disso? porque caso isso aconteça, o espaço na memória terá informações que não conseguem ser acessadas
	
	dataCapacity = other.dataCapacity;
	dataSize = other.dataSize;
	//data = other.data; //por que nao podemos fazer isso? porque ao fazer isso estamos criando a possibilidade de alterar os dois simultaneamente, além disso vai ser um double free, pois o primeiro vetor foi desalocado anteriormente ja
	data = new T[dataCapacity];
	for(int i=0;i<dataSize;i++) 
		data[i] = other.data[i];
	return *this;
}

template<class T2>
std::ostream& operator<<(std::ostream &out, const MyVec<T2> &v) {
	out << "Size: " << v.size() << "\n";
	out << "Capacity: " << v.dataCapacity << "\n";
	for(int i=0;i<v.size();i++) out << v.data[i] << " ";
	out << "\n";
	return out;
}

#endif