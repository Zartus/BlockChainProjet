package projetS4.src.projetS4;

import java.util.ArrayList;
import java.util.Calendar;
import java.util.List;

public class Block {
	private int index;//numero du block dans la chaine
	private String timestamp; //date au moment de la cr�ation
	private String previousHash;//
	private int nbTransaction;
	private List<Transaction> list;//liste de transaction 
	//private String hashRoot;//pas encore utiliser
	private String hash="";
	private int nonce;
	
	/*On introduit dans le contenu de chaque bloc un entier initialisé à zéro et appelé "nonce". Si le hash du
	bloc (incluant la nonce) ne satisfait pas le critére, on incrémente la nonce et on recommence le calcul du
	hash. On répéte ce processus jusqu'a ce que le hash satisfasse le crit�re (la difficulté). Ce calcul est appelé
	minage [mining].*/
	
	public Block(String previousHash,int nbTransaction,int index) {
		this.list=new ArrayList<Transaction>();
		this.nonce=0;
		this.setPreviousHash(previousHash);
		this.setNbTransaction(nbTransaction);
		this.timestamp= Calendar.getInstance().getTime().toString();
		this.nbTransaction=0;
		this.index=index;
	}
	
	/*
	public void makeTransaction(String transac) {
		//faire une lecture d'un fichier ici ?? pas bien compris à voir
		Transaction Trans = new Transaction();
		list.add(e)
	}*/
	
	public String getHash() {
		return hash;
	}
	
	public void setHash(String hash) {
		/*Incrementation a chaque fois qu'on modifie le hash du block*/
		this.nonce++;
		this.hash = hash;
	}
	
	public int getnonce() {
		return nonce;
	}
	
	public int getindex() {
		return index;
	}

	public int getNbTransaction() {
		return nbTransaction;
	}

	public void setNbTransaction(int nbTransaction) {
		this.nbTransaction = nbTransaction;
	}

	public String getPreviousHash() {
		return previousHash;
	}

	public void setPreviousHash(String previousHash) {
		this.previousHash = previousHash;
	}
	
	/**
	 * Methode qui permet le minage
	 * @param difficulté
	 */
	public void minage(String difficulte) {
		
		do {
			
			this.setHash(projetS4.src.projetS4.HashUtil.applySha256(this.toString()));
		}while(!this.getHash().startsWith(difficulte));
		
	}
	
	public String toString() 
    {
		String defBlock="";
		
		for(int i=0;i<this.nbTransaction;++i) {
			defBlock+=list.get(i).toString();
			defBlock+=" ";
		}
		
        return this.timestamp + this.previousHash + defBlock + nonce;
    } 
}
