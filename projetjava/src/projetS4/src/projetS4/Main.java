package projetS4.src.projetS4;

public class Main {
	public static void main(String [] args) {
		//on mine le hash
		System.out.println("Debut");
		int difficulte=4;
		
		BlockChain chaine = new BlockChain(difficulte);
		
	    chaine.addBlock();
	    
	    System.out.println("Fin");
	}
}
