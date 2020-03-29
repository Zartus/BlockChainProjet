package Blockchain;

import java.util.ArrayList;
import java.util.Random;

public class BlockChain {
	private static final int nbTransactionmax=10;
	private int difficulty;
	private int nbBlock;
	private String chaineDifficulty;
	private ArrayList<Block> list;
	
	public BlockChain(int difficulty) {
		this.difficulty=difficulty;
		this.list=new ArrayList<Block>();
		
		//generation du premier block
		Block Genesis = new Block("0",1,0);
		//genesis a une transaction et c'est "Genesis"
		
		this.list.add(Genesis);
		this.nbBlock=1;
		this.chaineDifficulty=difficultyDetermination();
	}
	
	/**
	 * getter qui permet d'acceder aux nombre de bloc de la blockchain
	 * @return
	 */
	public int getNbBlock() {
		return nbBlock;
	}
	
	/**
	 * Methode qui permet d'ajouter un block dans la blockchain
	 */
	public void addBlock() {
		//generation du nombre de transaction aux hasard
		Block element = new Block(this.list.get(this.nbBlock-1).getHash(),this.nbTransaction(),this.nbBlock);
		element.minage(difficultyDetermination());
		//on mine le block peut etre a mettre dans la classe block je sais pas encore
		
		this.list.add(element);
		this.nbBlock++;
		System.out.println("Le block a été ajouter");
	}
	
	/**
	 * Methode qui permet de crée un nouveau block
	 */
	public void createBlock() {
		
		this.nbBlock++;
		this.list.add(new Block(this.list.get(this.nbBlock-1).getHash(),this.nbTransaction(),this.nbBlock));
		
	}
	
	/**
	 * Methode qui permet d'ajouter une transaction dans le boucle current
	 * @param trans
	 */
	public void addTransaction(Transaction trans) {
		if(!this.list.get(this.nbBlock-1).addTransaction(trans)) {
			this.list.get(this.nbBlock-1).minage(this.chaineDifficulty);
			this.createBlock();
		}
	}
	
	/**
	 * Fonction qui permet de definir le nombre de transaction dans un block
	 * @return le nombre de transaction
	 */
	private int nbTransaction() {
		Random nombre=new Random();
		return nombre.nextInt(this.nbTransactionmax)+1;
	}
	
	/**
	 * Permet de savoir combien de 0 on va devoir chercher
	 * @return la chaine de caractere avec les 0 dedans
	 */
	private String difficultyDetermination() {
		String chaine="";
		System.out.println(this.difficulty);
		for(int i=0;i<this.difficulty;++i) {
			chaine=chaine+'0';
		}
		
		return chaine;
	}

	public String getChaineDifficulty() {
		return chaineDifficulty;
	}
}