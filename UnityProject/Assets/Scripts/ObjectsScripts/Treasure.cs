using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Treasure : MonoBehaviour
{
    public GameObject treasureChest;

    private int scorePoints;


    public void OnTriggerEnter(Collider collider)
    {
        if (collider.gameObject.tag == "Player")
        {
            collider.gameObject.GetComponent<PlayerMovement>().lostLifes -= 1;
            collider.gameObject.GetComponent<PlayerMovement>().score += 200;
            treasureChest.GetComponent<Animation>().Play();
            Debug.Log("Jugador obtiene cofre: " + collider.gameObject.GetComponent<PlayerMovement>().score);
            //Destroy(gameObject);
        }
    }

    public void setScorePoints(int _scorePoints) {
        scorePoints = _scorePoints;
    }

}
