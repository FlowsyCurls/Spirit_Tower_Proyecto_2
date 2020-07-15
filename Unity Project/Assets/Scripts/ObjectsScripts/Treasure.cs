using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Treasure : MonoBehaviour
{
    public GameObject treasureChest;
    public bool isOpen;

    private int scorePoints;

    private void Start()
    {
        isOpen = false;
    }

    public void OnTriggerEnter(Collider collider)
    {
        if (collider.gameObject.tag == "Player" && !isOpen)
        {
            if (collider.gameObject.GetComponent<PlayerMovement>().lifes != 5)
                collider.gameObject.GetComponent<PlayerMovement>().lifes++;

            collider.gameObject.GetComponent<PlayerMovement>().score += 200;
            treasureChest.GetComponent<Animation>().Play();
            Debug.Log("Jugador obtiene cofre: " + collider.gameObject.GetComponent<PlayerMovement>().score);
            isOpen = true;
            //Destroy(gameObject);
        }
    }

    public void setScorePoints(int _scorePoints) {
        scorePoints = _scorePoints;
    }

}
