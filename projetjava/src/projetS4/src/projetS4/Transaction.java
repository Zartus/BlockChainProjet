package projetS4.src.projetS4;

import java.util.Calendar;

public class Transaction {
	private int index;
	//type de l'evenement ? //nouvelle clef de chiffrage, nouvelle clef de signature ou nouvelle clef de chiffrement
	private String timestamp;
	private String transmitter;//identite de l'emeteur
	private String email;
	private String publicKey;//clef publique probablement (je sais pas si c'est int ou String)
	private String privateVerif;//clef de verification (je sais pas non plus si c'est int ou string)
	
	public Transaction(String transmitter,String email) {//manque des choses dans le constructeur mais c'est pour avancer
		this.email=email;
		this.transmitter=transmitter;
		this.timestamp= Calendar.getInstance().getTime().toString();
		//ajouter les autres informations
	}
	
	/**
	 * Retourne une chaine de caractere correspondant � la description d'une transaction
	 */
	public String toString() 
    {
        return timestamp + " " + transmitter + " " + email + " " + publicKey + " " + privateVerif; 
    }

	public int getIndex() {
		return index;
	} 
	
}
