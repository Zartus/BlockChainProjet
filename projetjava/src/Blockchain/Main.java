package Blockchain;

public class Main {
	public static void main(String [] args) {
		//on mine le hash
		System.out.println("Debut");
		int difficulte=6;
		
		BlockChain chaine = new BlockChain(difficulte);
		
	    chaine.addBlock();
	    
	    System.out.println("Fin");
	}
}
