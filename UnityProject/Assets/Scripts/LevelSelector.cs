using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class LevelSelector : MonoBehaviour
{
    // Start is called before the first frame update


    public void playLevel1()
    {

        Program.Start();
        Program.sendMessage("play_level01");
        Debug.Log("Recibiendo el mapa a cargar desde el servidor..");
        GameManager.setMapData(Program.receiveMessage());
        Program.sendMessage("getEntitys");
        GameManager.setEntityData(Program.receiveMessage());
        SceneManager.LoadScene(2);


    }
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        
    }
}
