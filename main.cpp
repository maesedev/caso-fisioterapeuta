#include <iostream>
#include <string.h>
#include <fstream>

using namespace std;

int pacOter,opcionPaciente,opcionTerapeuta;
int datoaEditar, indiceUsuario;
string cedula;
string matrizHistoriaClinica[9][12];
string chat[9][50];
string matrizSeguimientoTratamientos[9][42];
string tratamientos[5][32];//se declara la matriz con todos los tratamientos de la empresa
string terapeutaUser = "usuario";
string terapeutaPass = "123456789";


    //////  funciones   //////



bool enviarMensaje(string usuario,int indice){
    string mensaje;
    cout<<"\nIngrese el mensaje: ";
    getline(cin>>ws>>ws,mensaje);
    int indiceLibre = 1;

    for(int i=1; i<50 ;i++){
        if( !( chat[indice][i][0] )){
            indiceLibre = i;
            break;
        }
    }

    if(mensaje=="EXIT"){
        return false;
    }
    if(usuario=="paciente"){
        chat[indice][indiceLibre] = "Paciente:  " + mensaje; 
    }
    if(usuario == "terapeuta"){
        chat[indice][indiceLibre] = "Terapeuta: " + mensaje; 
    }
    
    return true;

}



void mostrarConversacion(int indiceUsuario){
   
    string nombreUsuarioChat = chat[indiceUsuario][0];
    
    for(int i=0;  i<5 ; i++ ){
        
    	//Evitar mostrar el nombre que esta en chat[fila del arr][0]
    	if( nombreUsuarioChat == chat[indiceUsuario][i] ) {
    		continue;
		}
		
		
    	if( chat[indiceUsuario][i][0]){
    		cout << chat[indiceUsuario][i] <<endl;
    	}
	} 
        
}

void mostrarConversaciones(){
    int opcion;
    bool hayConvs = false;
    // revise la segunda fila a algo que no sea 0

    for(int fila=0; fila < 9;fila++){
        if(     chat[fila][1][0]  ){
            cout<<"["<< fila + 1<<"] "<<matrizHistoriaClinica[fila][0]<<endl;
            hayConvs = true;
        }

    }
    if(hayConvs){

        // muestre esa conversacion con un indice [n]
        cout << "¿Que conversacion quiere abrir? (indice): ";cin>>opcion;
        opcion -=1; 
        while(opcion < 0 || opcion > 8){
            cout<<"Por favor introdusca un indice valido: ";cin>>opcion;
            opcion -=1; 
        }
        indiceUsuario = opcion; 

        for(int fila=0; fila < 9;fila++){
            if(     !( chat[fila][1]  ==  "0" ) &&  fila == opcion && !( chat[fila][1]  ==  "EXIT" ) ){
                mostrarConversacion(indiceUsuario);
            }
        }

        system("cls");
        
        cout<<"***** Para salir escriba EXIT *********\n\n"<<endl;
        mostrarConversacion(indiceUsuario);
        while( enviarMensaje("terapeuta",indiceUsuario) ){
            system("cls");

            cout<<"***** Para salir escriba EXIT *********"<<endl;
            mostrarConversacion(indiceUsuario);

            //enviar mensaje nuevo
        }
    }else{
        system("cls");
        cout << "******************************************\n\n";
        cout << "Por el momento no tienes conversaciones :)\n";
        cout << "\n******************************************\n";
    }
    
}



void paciente_enviarEvidencia(){
	cout<<"Ingrese al siguiente formulario: https://forms.gle/k9qX4HoQHc44pwYj8 llene los datos necesarios, elija la semana a mostrar evidencias y suba los archivos multimedia correspondientes."<<endl;
}

void terapeuta_verEvidencia(){
	system("cls");
	cout<<"Ingrese a la siguiente carpeta de drive: \nhttps://drive.google.com/drive/folders/1pwVkevpWI0-rbD73tKx3KKUqTty5NUlZkUYPb88vnPL1bO5KrS9vZpWB1cUpMcFsuo-dgnmc?usp=sharing \npara ver las evidencias de cada paciente."<<endl;
}

void verEjerciciosPaciente(string cedula){
	int id=0,opcionsemana;
	char desea;
	for (int filas=0;filas<9;filas++){
		if(cedula==matrizSeguimientoTratamientos[filas][1]){
			id=filas;
		}
	}
	
	do{
		cout<<"El paciente tiene un plan de ejercicios de 10 semanas. \nElija la semana a revisar (1-10): ";
		cin>>opcionsemana;
		
		cout<<"\n\n<<Semana "<<opcionsemana<<">>"<<endl;
		cout<<"---->Ejercicio: \n"<<matrizSeguimientoTratamientos[id][2+4*(opcionsemana-1)]<<"\n\n";
		cout<<"---->Descripcion: \n"<<matrizSeguimientoTratamientos[id][3+4*(opcionsemana-1)]<<"\n\n";
		cout<<"---->Link de YouTube: "<<matrizSeguimientoTratamientos[id][4+4*(opcionsemana-1)]<<"\n\n";
		cout<<"Desea ver otra semana? (S/N): ";
		cin>>desea;
	}while(desea=='s'||desea=='S');
	
	
}

void modificarEjerciciosPaciente(){
	int id=0,aux=1,ejercicioreemplazar, opcionsemana;
	cout<<"Ingrese la C�dula del paciente: ";
	cin>>cedula;
	for (int filas=0;filas<9;filas++){
		if(cedula==matrizSeguimientoTratamientos[filas][1]){
			id=filas;
		}
	}
	cout<<"El paciente tiene un plan de ejercicios de 10 semanas. Elija la semana a modificar(1-10): "<<endl;
	cin>>opcionsemana;
	system("cls");
	cout<<"----------------------------------------"<<endl;
	cout<<"Ejercicio ACTUAL: Semana "<<opcionsemana<<" :"<<endl;
	cout<<"Tratamiento: "<<matrizSeguimientoTratamientos[id][2+4*(opcionsemana-1)]<<endl;
	cout<<"----------------------------------------"<<endl;
	
	cout<<"Elija el ejercicio a reemplazar: "<<endl;
	for (int columnas=2;columnas<42;columnas+=4){
    		cout<<" "<<aux<<": "<<matrizSeguimientoTratamientos[id][columnas]<<endl;
    		aux+=1;//se muestran los ejercicios que el paciente debe realizar segun el tratamiento
	}
	cin>>ejercicioreemplazar;
	
    matrizSeguimientoTratamientos[id][2+4*(opcionsemana-1)]=matrizSeguimientoTratamientos[id][2+4*(ejercicioreemplazar-1)];
    matrizSeguimientoTratamientos[id][3+4*(opcionsemana-1)]=matrizSeguimientoTratamientos[id][3+4*(ejercicioreemplazar-1)];
    matrizSeguimientoTratamientos[id][4+4*(opcionsemana-1)]=matrizSeguimientoTratamientos[id][4+4*(ejercicioreemplazar-1)];
	
	cout<<"Cambio de ejercicio en la semana"<<opcionsemana<<" realizado satisfactoriamente"<<endl;
	
}

void mostrarTratamiento(string cedula){

	int id=0;
	for (int i=0;i<9;i++){
		if(cedula==matrizHistoriaClinica[i][1]){
			id=i;
            break;
		}
	}
	
	cout<<"El tratamiento formulado por el terapeuta es: "<<matrizSeguimientoTratamientos[id][0]<<endl;
	
}

void rellenarCerosMatrizPaciente(){
	int k,j;
	for (k=0;k<=8;k++) //deja la matriz con todos los datos en 0 en el inicio para poder manipular mejor las funciones
	{
		for (j=0;j<=11;j++)
		{
			matrizHistoriaClinica[k][j]="0";
		}
	}
}

void matrizTratamientos(){ //llenar la matriz que contiene todos los tratamientos
    
    ifstream file("tratamientos.txt");
    for (int filas=0;   filas<5;      filas++){ 
        for(int columnas=0;     columnas<32;    columnas++){
            getline(file,tratamientos[filas][columnas]); //se utiliza un archivo txt que contiene los datos de los tratamientos y ejercicios para llenar la matriz
        }
    }
    
}

void llenartratamientopaciente(int id){
	int aux=2,opcion;
	cout<<"-------------------------------------------------------------"<<endl;
    system("cls");
	cout<<"-------------------------TRATAMIENTO-----------------------------"<<endl;
    cout<<"        Elija alguno de los tratamientos disponibles: \n"<<endl; //se muestran todos los tratamientos de la empresa
	for (int filas=0;   filas<5;      filas++){ 
        cout<<"["<<filas+1 <<"] TRATAMIENTO NO. "<<filas+1<<":\n----------->"<<tratamientos[filas][0]<<"\n"<<"Descripcion:\n"<<tratamientos[filas][1]<<"\n\n"; 
    }
    do{
        cout<<"Ingrese una opcion de tratamiento: ";cin>>opcion;
        
        //se elige un tratamiento para el paciente
	}while(opcion>5||opcion<1);
    system("cls");
    
    
    matrizSeguimientoTratamientos[id-1][0]=tratamientos[opcion-1][0]; //se llena en la matriz el apartado de "nombre del tratamiento"
    for (int columnas=2;columnas<42;columnas+=4){ //se llena en la matriz en las columnas de ejercicios de cada semana los ejercicios establecidos en el tratamiento
    	matrizSeguimientoTratamientos[id-1][columnas]=tratamientos[opcion-1][aux];
    	matrizSeguimientoTratamientos[id-1][columnas+1]=tratamientos[opcion-1][aux+1];
    	matrizSeguimientoTratamientos[id-1][columnas+2]=tratamientos[opcion-1][aux+2];
    	aux+=3;
	}
	cout<<"------------------------------------------------------"<<endl;
	cout<<"Se eligio el tratamiento: "<< matrizSeguimientoTratamientos[id-1][0]<<endl<<". Los ejercicios que debe realizar cada semana el paciente son: "<<endl;
	
	aux=1;
	for (int columnas=2;columnas<42;columnas+=4){
    		cout<<" Semana "<<aux<<": "<<matrizSeguimientoTratamientos[id-1][columnas]<<endl;
    		aux+=1;//se muestran los ejercicios que el paciente debe realizar segun el tratamiento
	}
	cout<<"------------------------------------------------------"<<endl;
	cout<<"d. FECHAS DE CONTROL PRESENCIAL: Escriba las fechas y hora la cual se va a encontrar con el paciente:"<<endl;//se debe escribir las fechas presenciales con el paciente
	getline(cin>>ws >> ws, matrizSeguimientoTratamientos[id-1][1]);
	cout<<"------------------------------------------------------"<<endl;
    system("cls");
}
bool usuarioExiste(string cedula){
    for(int i=0; i < 9;i++){
        if(matrizHistoriaClinica[i][1] == cedula){
            return true;
        }
    }
    cout<<"No hay un paciente con cedula "<<cedula<<" en la base de datos, intentalo de nuevo..."<<endl; 

    return false;
}

bool cedulaexiste(string cedula){
	int count=0;

	for (int filas=0;filas<9;filas++){
		if(matrizHistoriaClinica[filas][1]==cedula){
            indiceUsuario=filas;
			count++;
		}
	}
	if (count>=2){
		return true;
	}
	else{
		return false;
	}
}

void llenardatos(){
	int i, s=0;
	while (matrizHistoriaClinica[s][0]!="0") //verificar cual fila (paciente) de la matriz esta vacio para llenar la informacion (sirve por si se eliminan pacientes, asi se rellenan las filas sin dejar espacios)
	{
		s+=1;
	}
	
	cout<<"REGISTRO PACIENTE # "<<s+1<<endl;
	cout<<"------------------------------------------------------"<<endl;
	for (i=1;i<=12;i++) //registro de los datos del paciente
	{
		switch(i){
			case 1:
				cout<<"a. Informacion general. Ingrese los siguientes datos del paciente."<<endl;
				cout<<" 1. Nombre del paciente: ";
			    break;
			case 2:
				cout<<" 2. Cedula: ";
			    break;
			case 3:
				cout<<" 3. Edad: ";
			    break;
			case 4:	
				cout<<" 4. Sexo (M/F): ";
			    break;
			case 5:
				cout<<" 5. Ocupacion: ";
			    break;
			case 6:
				cout<<"------------------------------------------------------"<<endl;
				cout<<"b. HISTORIA CLINICA. Ingrese los siguientes datos del paciente."<<endl;
				cout<<" 1. Antecedentes personales: ";
			    break;
			case 7:
				cout<<" 2. Antecedentes familiares: ";
			    break;
			case 8:
				cout<<" 3. S�ntomas que presenta el paciente: ";
			    break;
			case 9:
				cout<<" 4. Peso (en kg): ";
			    break;
			case 10:
				cout<<" 5. Altura (en metros): ";
			    break;
			case 11:
				cout<<" 6. Frecuencia de ejercicio del paciente: ";
			    break;
			case 12:
				cout<<" 7. Diagnostico segun lo establecido: ";
			    break;
			default: 
            cout<<"Error";
            break;
		}
		getline(cin>>ws>>ws,matrizHistoriaClinica[s][i-1]);
		
		if(i==1){
		    chat[s][0] = matrizHistoriaClinica[s][i-1];
		}

	}

    while(cedulaexiste(matrizHistoriaClinica[s][1])){

        cout<<"Ya existe un paciente con esta cedula..."<<endl; 
        cout<<"ingrese de nuevo su nombre: ";
        getline(cin>>ws>>ws,matrizHistoriaClinica[s][0]);
        cout<<"ingrese de nuevo su cedula: ";
        getline(cin>>ws>>ws,matrizHistoriaClinica[s][1]);

    }

	llenartratamientopaciente(s+1);
	cout<<"------------------------*****Enhorabuena*****------------------------"<<endl;
    cout<<"ha finalizado el registro del paciente con cedula <"<<matrizHistoriaClinica[s][1]<<">\nCon la cedula puede editar, eliminar y modificar datos y ejercicios del paciente en las opciones respectivas."<<endl;
}

void registroDePacientes(){
	
	cout<<"----------------------AFILIADOS------------------------"<<endl;
	cout<<"Los pacientes afiliados actualmente en la empresa son: "<<endl;
	for(int filas=0;filas<9;filas++){
		if (matrizHistoriaClinica[filas][0]!="0") //se valida, si la primera columna contiene 0 no cumple la condición, es porque el resto de las columnas tambien estan vacias (por la funcion de poner 0 a toda la matriz al inicio del programa)
			cout<<"-------> Paciente No. "<<filas+1<<": "<<matrizHistoriaClinica[filas][0]<<"   C.C No. "<<matrizHistoriaClinica[filas][1]<<endl;
	}
	
}

void eliminarPaciente(){
	int id;
	char opcion;
	cout<<"Escriba la cedula del paciente a eliminar: ";
	cin>>cedula;
	
	for (int filas=0;filas<9;filas++){
		if(cedula==matrizSeguimientoTratamientos[filas][1]){
			id=filas;
		}
	}
	
	cout<<"El paciente con Cedula #"<<cedula<<", llamado"<<matrizHistoriaClinica[id][0]<<" va a ser eliminado del registro, esta seguro? S/N";
	cin>>opcion;
	if(opcion=='S'||opcion=='s'){
		for (int j=0;j<=11;j++)
		{
			//se elimina el registro del paciente dejando la fila en ceros, para poder agregar otro paciente con la funcion llenartratamientopaciente
			matrizHistoriaClinica[id][j]="0";
            //eliminar conversacion
		}
		cout<<"El paciente fue eliminado del registro satisfactoriamente"<<endl;
	}
	else{
		cout<<"No se elimino el paciente."<<endl;
	}
}

void paciente_consultarFechasPresenciales(string cedula){
	
	for (int filas=0;filas<9;filas++){
		if(cedula==matrizSeguimientoTratamientos[filas][1]){
            cout<<"Las fechas de control presencial establecidas por su terapeuta son: "<<matrizSeguimientoTratamientos[filas][1]<<endl;
            cout<<"----------------------------------------------------------------------------------------------"<<endl;
            break;
        }
	}
	
	
}

void terapeuta_editarfechaspresenciales(){
	char opcion;
	string id;
	cout<<"Ingrese la cedula del paciente: ";
	cin>>id;
	for(int i=0;i<9;i++){
		if(matrizHistoriaClinica[i][1] == id){
			cout<<"ingrese las nuevas fechas de consulta presenciales: ";
			getline(cin>>ws >> ws,matrizSeguimientoTratamientos[i][1]);
			cout<<"-----------------***** Cambio realizado exitosamente *****-----------------"<<endl;
			break;
		}
		if(i==8){
			cout<<"no se encontro el paciente con la cedula "<<id<<endl;
		}
	}
}

void editarNombre(){
    string nuevoNombre;
    cout<<"Ingrese la cedula del paciente al que se le va a editar el nombre: ";
    getline(cin>>ws,cedula);

    cout<<"Ingrese el nuevo nombre: ";
    getline(cin>>ws,nuevoNombre);

    for(int i = 0 ; i < 9;i++){
        string nombreAntiguo = matrizHistoriaClinica[i][0];
        if(cedula == matrizHistoriaClinica[i][1]){
            matrizHistoriaClinica[i][0] = nuevoNombre;
            chat[i][0];
            cout<<"nombre del paciente "<< i <<" cambiado de <"<< nombreAntiguo <<"> a <"<<matrizHistoriaClinica[i][0]<<"> satisfactoriamente..."<<endl;
            
        break;
        }

        if(i == 8){
            cout<<"Lo sentimos no hay un paciente con la cedula "<<cedula<<endl;

        }
    }
}

void editarCedula(){
    string nuevaCedula;
    cout<<"Ingrese la cedula del paciente al que se le va a editar la cedula: ";
    getline(cin>>ws,cedula);
    cout<<"Ingrese la nueva cedula del paciente: ";
    getline(cin>>ws,nuevaCedula);

    for(int i = 0 ; i < 9;i++){
        if(cedula == matrizHistoriaClinica[i][1]){
            matrizHistoriaClinica[i][1] = nuevaCedula;

            cout<<"La cedula se actualizo de <"<<cedula<<"> a <"<< matrizHistoriaClinica[i][1]<<"> satisfactoriamente..."<<endl;
            
        break;
        }

        if(i == 8){
            cout<<"Lo sentimos no hay un paciente con la cedula "<<cedula<<endl;

        }
    }
}

void editarEdad(){

    string nuevaEdad;
    cout<<"Ingrese la cedula del paciente al que se le va a editar la edad: ";
    getline(cin>>ws,cedula);
    cout<<"Ingrese la nueva edad: ";
    getline(cin>>ws,nuevaEdad);

    for(int i = 0 ; i < 9;i++){
        string edadAntigua = matrizHistoriaClinica[i][2];
        if(cedula == matrizHistoriaClinica[i][1]){
            matrizHistoriaClinica[i][2] = nuevaEdad;

            cout<<"La edad se actualizo de <"<<edadAntigua<<"> a <"<< matrizHistoriaClinica[i][2] <<"> satisfactoriamente..."<<endl;
            
        break;
        }

        if(i == 8){
            cout<<"Lo sentimos no hay un paciente con la cedula "<<cedula<<endl;

        }
    }
}

void editarSexo(){
    string nuevoSexo;

    cout<<"Ingrese la cedula del paciente al que se le va a editar el sexo: ";
    getline(cin>>ws,cedula);
    cout<<"Ingrese el nuevo sexo: ";
    getline(cin>>ws,nuevoSexo);
    for(int i = 0 ; i < 9;i++){
        string sexoAntiguo = matrizHistoriaClinica[i][3];

        if(cedula == matrizHistoriaClinica[i][1]){
            matrizHistoriaClinica[i][3] = nuevoSexo;

            cout<<"El sexo de "<< matrizHistoriaClinica[i][0]<<" se cambio de <" <<sexoAntiguo<<"> a <"<< matrizHistoriaClinica[i][3] <<"> satisfactoriamente..."<<endl;
            
        break;
        }

        if(i == 8){
            cout<<"Lo sentimos no hay un paciente con la cedula "<<cedula<<endl;

        }
    }
}

void editarOcupacion(){
    string nuevaOcupacion;

    cout<<"Ingrese la cedula del paciente al que se le va a editar la ocupacion: ";
    getline(cin>>ws,cedula);
    cout<<"Ingrese la nueva ocupacion del paciente: ";
    getline(cin>>ws,nuevaOcupacion);
    for(int i = 0 ; i < 9;i++){
        string antiguaOcupacion = matrizHistoriaClinica[i][4];

        if(cedula == matrizHistoriaClinica[i][1]){
            matrizHistoriaClinica[i][4] = nuevaOcupacion;

            cout<<"La ocupacion de "<< matrizHistoriaClinica[i][0]<<" se cambio de <" <<antiguaOcupacion<<"> a <"<< matrizHistoriaClinica[i][4] <<"> satisfactoriamente..."<<endl;
            
        break;
        }

        if(i == 8){
            cout<<"Lo sentimos no hay un paciente con la cedula "<<cedula<<endl;

        }
    }
}

void editarAntecedentesPersonales(){
    string nuevosAntecedentes;

    cout<<"Ingrese la cedula del paciente al que se le va a editar los antecedentes personales: ";
    getline(cin>>ws,cedula);
    for(int i = 0 ; i < 9;i++){

        if(cedula == matrizHistoriaClinica[i][1]){
            cout<<" ------------------antecedentes personales-------------------- "<<endl;
            cout<<matrizHistoriaClinica[i][5]<<endl;
            cout<<"\nIngrese los nuevos antecedentes: ";
            getline(cin>>ws,nuevosAntecedentes);

            matrizHistoriaClinica[i][5] = nuevosAntecedentes;

            cout<<"antecedentes cambiados satisfactoriamente..."<<endl;
            
        break;
        }

        if(i == 8){
            cout<<"Lo sentimos no hay un paciente con la cedula "<<cedula<<endl;

        }
    }
}

void editarAntecedentesFamiliares(){
    string nuevosAntecedentes;

    cout<<"Ingrese la cedula del paciente al que se le va a editar los antecedentes familiares: ";
    getline(cin>>ws,cedula);
    for(int i = 0 ; i < 9;i++){

        if(cedula == matrizHistoriaClinica[i][1]){
            cout<<" ------------------antecedentes-------------------- "<<endl;
            cout<<matrizHistoriaClinica[i][6]<<endl;
            cout<<"\nIngrese los nuevos antecedentes: ";
            getline(cin>>ws,nuevosAntecedentes);

            matrizHistoriaClinica[i][6] = nuevosAntecedentes;

			system("cls");
			
            cout<<"\n---------------------------------------------------\n"<<endl;
            cout<<"   antecedentes cambiados satisfactoriamente..."<<endl;
            cout<<"\n---------------------------------------------------\n"<<endl;
            
        break;
        }

        if(i == 8){
            cout<<"Lo sentimos no hay un paciente con la cedula "<<cedula<<endl;

        }
    }
}

void editarSintomas(){
    string nuevosAntecedentes;

    cout<<"Ingrese la cedula del paciente al que se le va a editar los sintomas: ";
    getline(cin>>ws,cedula);
    for(int i = 0 ; i < 9;i++){

        if(cedula == matrizHistoriaClinica[i][1]){
            cout<<" ------------------SINTOMAS-------------------- "<<endl;
            cout<<matrizHistoriaClinica[i][7]<<endl;
            cout<<"\nIngrese los nuevos sintomas: ";
            getline(cin>>ws,nuevosAntecedentes);

            matrizHistoriaClinica[i][7] = nuevosAntecedentes;

            cout<<"Sintomas cambiados satisfactoriamente..."<<endl;
            
        break;
        }

        if(i == 8){
            cout<<"Lo sentimos no hay un paciente con la cedula "<<cedula<<endl;

        }
    }
}

void editarPeso(){

    string nuevoPeso;
    cout<<"Ingrese la cedula del paciente al que se le va a editar el peso: ";
    getline(cin>>ws,cedula);
    cout<<"Ingrese el nuevo peso: ";
    getline(cin>>ws,nuevoPeso);

    for(int i = 0 ; i < 9;i++){
        string edadAntigua = matrizHistoriaClinica[i][8];
        if(cedula == matrizHistoriaClinica[i][1]){

            matrizHistoriaClinica[i][8] = nuevoPeso;
            cout<<"El peso se actualizo de <"<<edadAntigua<<"> a <"<< matrizHistoriaClinica[i][8] <<"> satisfactoriamente..."<<endl;
            
        break;
        }

        if(i == 8){
            cout<<"Lo sentimos no hay un paciente con la cedula "<<cedula<<endl;

        }
    }
}

void editarAltura(){

    string nuevaAltura;
    cout<<"Ingrese la cedula del paciente al que se le va a editar la altura: ";
    getline(cin>>ws,cedula);
    cout<<"Ingrese la nueva altura: ";
    getline(cin>>ws,nuevaAltura);

    for(int i = 0 ; i < 9;i++){
        string antiguaAltura = matrizHistoriaClinica[i][9];
        if(cedula == matrizHistoriaClinica[i][1]){
            matrizHistoriaClinica[i][9] = nuevaAltura;

            cout<<"La altura se actualizo de <"<<antiguaAltura<<"> a <"<< matrizHistoriaClinica[i][9] <<"> satisfactoriamente..."<<endl;
            
        break;
        }

        if(i == 8){
            cout<<"Lo sentimos no hay un paciente con la cedula "<<cedula<<endl;

        }
    }
}

void editarFrecuenciaEjercicio(){

    string nuevaFrecuencia;
    cout<<"Ingrese la cedula del paciente al que se le va a editar la frecuencia de ejercicio: ";
    getline(cin>>ws,cedula);
    cout<<"Ingrese la nueva frecuencia de ejercicio: ";
    getline(cin>>ws,nuevaFrecuencia);

    for(int i = 0 ; i < 9;i++){
        string antiguaFrecuencia = matrizHistoriaClinica[i][10];
        if(cedula == matrizHistoriaClinica[i][1]){
            matrizHistoriaClinica[i][10] = nuevaFrecuencia;

            cout<<"La frecuencia de ejercicio se actualizo de <"<<antiguaFrecuencia<<"> a <"<< matrizHistoriaClinica[i][10] <<"> satisfactoriamente..."<<endl;
            
        break;
        }

        if(i == 8){
            cout<<"Lo sentimos no hay un paciente con la cedula "<<cedula<<endl;

        }
    }
}

void editarDiagnostico(){

    string nuevoDiagnostico;
    cout<<"Ingrese la cedula del paciente al que se le va a editar el diagnostico: ";
    getline(cin>>ws,cedula);
    cout<<"Ingrese el nuevo diagnostico: ";
    getline(cin>>ws,nuevoDiagnostico);

    for(int i = 0 ; i < 9;i++){
        string antiguodiagnostico = matrizHistoriaClinica[i][11];
        if(cedula == matrizHistoriaClinica[i][1]){
            matrizHistoriaClinica[i][11] = nuevoDiagnostico;

            cout<<"El diagnostico se actualizo de <"<<antiguodiagnostico<<"> a <"<< matrizHistoriaClinica[i][11] <<"> satisfactoriamente..."<<endl;
            
        break;
        }

        if(i == 8){
            cout<<"Lo sentimos no hay un paciente con la cedula "<<cedula<<endl;

        }
    }
}

void ingreseValorValido(){
    cout<<"la opcion introducida no es valida, por favor ingrese un valor valido"<<endl;
}

bool hayPacientes(){
	bool var=false;
	for(int filas=0;filas<9;filas++)
	{
		if(matrizHistoriaClinica[filas][0]!="0"){
			var=true;
		}
	}
	return var;
}
////////////////////////////////////7

int main(){
    system("cls");
    char irPaAtras='s';
    char salirEditar='n';
    char salirInfoTratamientos='n';
    char cerrarSesion = 's';
    
    string userTry;
    string passTry;
	matrizTratamientos();
    rellenarCerosMatrizPaciente();

    do{
        cout<<"Ingresar como: \n1. paciente \n2. Terapeuta \nIngrese la opcion que corresponda: ";cin>>pacOter;
            switch (pacOter){
                case 1:
                    if( !hayPacientes()){
                        cout<<"                   ^             ^                     "<<endl;
                        cout<<"             _____/ \\___     __/ \\_______                "<<endl;
                        cout<<"        _______________     _______________          "<<endl;
                        cout<<"     ___________||               ||__________     "<<endl;
                        cout<<"  ________________)------------(____________________   "<<endl;
                        cout<<"______________________________________________________  "<<endl;
                        cout<<"\n\n\nLo siento no hay pacientes aún en el sistema...   "<<endl;
                        break;
                    }
                    cout<<"ingrese su cedula: ";cin>>cedula;

                    if(!usuarioExiste(cedula)){
                        break;
                    }
                        
                    system("cls");
                    do{
                        cout<<"\n1. Mi tratamiento \n2. Tareas realizar \n3. Control de evidencias\n4. Consultar sesiones presenciales";
                        cout<<"\n5. Comuniquese con el terapeuta \n6. Cerrar sesion \nIngrese una opcion: ";cin>>opcionPaciente;
                        
                        switch (opcionPaciente)
                        {
                            case 1:
                                mostrarTratamiento(cedula);
                                break;
                            
                            case 2:
                                verEjerciciosPaciente(cedula);
                                break;
                            
                            case 3:
                                paciente_enviarEvidencia();
                                break;
                            
                            case 4:
                                paciente_consultarFechasPresenciales(cedula);
                                break;
                            
                            case 5:
                                cout<<"***** Para salir escriba EXIT *********\n\n"<<endl;
                                mostrarConversacion(indiceUsuario);

                                while( enviarMensaje("paciente",indiceUsuario) ){
                                    system("cls");

                                    cout<<"***** Para salir escriba EXIT *********"<<endl;
                                    mostrarConversacion(indiceUsuario);

                                    //enviar mensaje nuevo
                                }
                                break;
                            
                            case 6:
                                cerrarSesion='n';
                                break;
                            
                            default:
                                ingreseValorValido();
                                break;
                        }


                    }while(cerrarSesion == 's');
                    break;
                
                case 2:
                    system("cls");
					cerrarSesion='s';
					salirEditar='n';
					irPaAtras='n';
                    
                    // credenciales

                    cout<<"ingrese usuario: ";cin>>userTry;
                    if(terapeutaUser != userTry){
                        cout<<"Usuario invalido..."<<endl;
                        break;
                    }
                    cout<<"Ingrese la contraseña: ";cin>>passTry;
                    if(terapeutaPass != passTry){
                        cout<<"contraseña invalida..."<<endl;
                        break;
                    }

                    do{
                        cout<<"\n1. Crear paciente \n2. Editar paciente \n3. Eliminar paciente \n4. Registro de pacientes";
                        cout<<"\n5. Informacion de tratamientos \n6. Conversaciones con pacientes \n7. cerrar sesion \nIngrese una opcion: ";cin>>opcionTerapeuta;
                        switch (opcionTerapeuta)
                        {
                            case 1:
                                llenardatos();
                                break;
                            
                            case 2:
                                int opcionaEditar;

                                system("cls");
                                cout<<"Elija la informacion a editar: \n1. Informacion personal \n2. Historia clinica \n3. ir atras\nIngrese una opcion: ";cin>>opcionaEditar;
                                do
                                {
                                    switch (opcionaEditar)
                                    {
                                        case 1:
                                            

                                            //Ingresar la cedula del paciente
                                            
                                            system("cls");
                                            
                                            do{
                                                cout<<"Que desea editar \n1. Nombre \n2. Cedula \n3. edad \n4. Sexo \n5. Ocupacion \n6. Ir atras \nIngrese una opcion: ";cin>>datoaEditar;
                                                
												switch (datoaEditar){
                                                    case 1:
                                                        editarNombre();
                                                        break;
                                                    
                                                    case 2:
                                                        editarCedula();
                                                        break;
                                                    
                                                    case 3:
                                                        editarEdad();
                                                        break;
                                                    
                                                    case 4:
                                                        editarSexo();
                                                        break;
                                                    
                                                    case 5:
                                                        editarOcupacion();
                                                        break;
                                                    case 6:
                                                    	salirEditar='n';
                                                        break;
                                        
                                                    default:
                                                        ingreseValorValido();
                                                        break;
                                                    }
                                            }while(salirEditar=='s');
                                            break;
                                        case 2:
                                            do
                                            {
												cout<<"Que desea editar \n1. Antecedentes Personales \n2. Antecedentes familiares \n3. Sintomas \n4. Peso \n5. altura \n6. Frecuencia de ejercicio \n7. Diagnostico \n8. Ir atras \nIngrese una opcion: ";cin>>datoaEditar;
										    
                                                switch (datoaEditar)
                                                {
                                                    case 1:
                                                        editarAntecedentesPersonales();
                                                        break;
                                                    
                                                    case 2:editarAntecedentesFamiliares();
                                                        break;
                                                    
                                                    case 3:
                                                        editarSintomas();
                                                        break;
                                                    
                                                    case 4:
                                                        editarPeso();
                                                        break;
                                                    
                                                    case 5:
                                                        editarAltura();
                                                        break;
                                                    case 6:
                                                        editarFrecuenciaEjercicio();
                                                        break;
                                                    
                                                    case 7:
                                                        editarDiagnostico();
                                                        break;
                                                    case 8:
                                                    	salirEditar='s';
                                                        break;
                                                    
                                                    default:
                                                        ingreseValorValido();
                                                        break;
                                                    }
                                            
                                            } while (salirEditar =='n');
                                            
                                            break;
                                        case 3: 
                                            irPaAtras='n';
											break;
                                        default:
                                            ingreseValorValido();
                                            break;
                                        }
                                    
                                } while (irPaAtras=='s');
                                

                                break;
                            case 3:
                                //Pedir cedula del paciente

                                eliminarPaciente();
                                break;
                            case 4: 
                                system("cls");
                                registroDePacientes();
                                break;
                            case 5:
                                //pedir cedula del paciente 

                                int opcInfoTratamientos;
                                system("cls");
                                do
                                {
                                cout<<"\n1. Ver tratamiento \n2. Editar actividades semanales \n3. Ver evidencias del paciente \n4. Editar citas presenciales";
                                cout<<"\n5. Ir atras \nIngrese una opcion: ";cin>>opcInfoTratamientos;
                                    
                                    switch (opcInfoTratamientos)
                                    {
                                        case 1:
                                            //Funcion para mostrar el tratamiento del paciente
                                            cout<<"Ingrese la cedula del paciente: ";cin >>cedula;
                                            system("cls");
                                            if(!usuarioExiste(cedula)){
                                                break;
                                            }
                                            mostrarTratamiento(cedula);
                                            break;
                                        
                                        case 2:
                                            //Funcion para editar las actividades semanales
                                            modificarEjerciciosPaciente();
                                            break;
                                        case 3:
                                            // mostrar el link de drive del paciente
                                            terapeuta_verEvidencia();
                                            break;
                                        case 4:
                                            // funcion para editar los encuentros presenciales
                                            terapeuta_editarfechaspresenciales();
                                            break;
                                        case 5:
                                        	salirInfoTratamientos='s';
                                            break;
                                        default:
                                            ingreseValorValido();
                                            break;
                                        }
                                } while (salirInfoTratamientos=='n');
                                
                                break;
                            case 6:
                                mostrarConversaciones();
                                break;
                            case 7:
                                cerrarSesion='n';
                                system("cls");
                                break;
                            default:
                                break;
                            }       
                    }while(cerrarSesion=='s');
                        break;
                    
                default:
                    break;
        }}
        
    while(true);
    return 0; 

}

/*
2
usuario
123456789
1
santiago garzon
12345
17
M
abogado
mucho dulce de joven
diabetes en familia
dolor de cabeza y espalda
120kg
1,7
baja
Hacer ejercicio2
2
16 enero y 24 de enero
7
1
12345
5
Hola doctor buen dia como me le va ¿todo bien?
Queria saber si podiamos encontrarnos para poder acelerar el proceso de recuperacion
EXIT

*/
