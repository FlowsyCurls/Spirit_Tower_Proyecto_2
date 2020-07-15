using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class MainMenu : MonoBehaviour
{

    public void goToSelector()
    {
        Program.Start();
        Program.sendMessage("play");
        Debug.Log("Recibiendo el mapa a cargar desde el servidor..");
        GameManager.setMapData(Program.receiveMessage());
        Program.sendMessage("getEntitys");
        GameManager.setEntityData(Program.receiveMessage());
        SceneManager.LoadScene(1);
    }

    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        
    }
}
