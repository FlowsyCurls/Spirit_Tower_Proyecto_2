using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;


public class Score : MonoBehaviour
{
    public GameObject player;

    public void FixedUpdate()
    {
        GetComponent<Text>().text = " " + player.gameObject.GetComponent<PlayerMovement>().score;
    }
}