using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Newtonsoft.Json;
using System.Threading;
using System.Runtime.ExceptionServices;

//Class that keeps the state of the game in the client side, tracks the player and enemy behavoir, sends data to server and call server petitions

class PlayerStatusJSON
{
    public int[] position = new int[2];
}

class CapsulaEntity
{
    public Entity[] listOfEntitys;
}

class Entity
{
    public string id;
    public int[] position;
    public string type;
}

class Matriz
{
    public int[][] matriz;
}

public class GameManager : MonoBehaviour
{

    public GameObject node;
    public GameObject enemy;
    public GameObject client;
    public GameObject player;

    public Color32 spectreGray;
    public Color32 spectreBlue;
    public Color32 spectreRed;
    public Color32 treasure;
    public Color32 jarron;
    public Color32 spectralEye;
    public Color32 mouse;
    public Color32 chuchu;

    int gridX = 20;
    int gridZ = 20;
    public float nodeSeparation;

    public GameObject[,] mat;
    public int enemyQuantity;

    public static string mapData;
    public static string entityData;

    private static List<GameObject> entitys;
    
    public static void setEntityData(string msg)
    {
        entityData = msg;
    }
    public static void setMapData(string msg)
    {
        mapData = msg;
    }

    private string generatePlayerPositionJSON()
    {
        PlayerStatusJSON p = new PlayerStatusJSON();
        p.position[0] = PlayerMovement.row;
        p.position[1] = PlayerMovement.column;

        return JsonConvert.SerializeObject(p);
    }

    void threadCommunicator()
    {
        Program.Start();
        Program.sendMessage(generatePlayerPositionJSON());
        entityData = Program.receiveMessage();
        updateEntitys();

    }



    // Start is called before the first frame update
    void Start()
    {
        //Create the matrix
        entitys = new List<GameObject>();
        createGrid();       //Create all nodes on matrix, and put them onto the structure
        createEntitys();

        //Program.Start();
        InvokeRepeating("threadCommunicator", 0, 0.5F);
        //Thread t = new Thread(new ThreadStart(threadCommunicator));
        //t.Start();
        
        //spawnEnemies();     //Spawn enemies on stage

    }

    // Update is called once per frame, keeps track of the player, at least at this early stage of the client-server communication
    void Update()
    {

        //If player is moving, send msg that he is moving
        //if (player.GetComponent<PlayerMovement>().getLastDir() != player.GetComponent<PlayerMovement>().getDir()) {
        //Debug.Log("Moviendose");
        //Send msg that the player is moving on a direction to server
        //Program.Start();
        //Program.sendMessage("Player is moving");
        //}
        //Thread.Sleep(1000);
        //Debug.Log("a");


        
    }


    //Creates all the nodes of the matrix and put them onto their respective position
    /*
    0 is the bottom left of the visualized matrix:
    
        ...
    [[0,1], [1,1]]
    [[0,0], [1,0]] ...
     
    */
    void createGrid() {

        mat = new GameObject[gridX, gridZ];     //Let a matrix of lenght nxm

        Matriz m = JsonConvert.DeserializeObject<Matriz>(mapData);

        for (int x = 0; x < gridX; x++)
        {
            for (int z = 0; z < gridZ; z++)
            {
                //Instantiate object, to create in map
                GameObject n = Instantiate(node, new Vector3(x * (node.transform.localScale.x + nodeSeparation), 0, z *- (node.transform.localScale.z + nodeSeparation)), Quaternion.identity);

                //Get the script, and set their x and y values of the matrix
                n.GetComponent<Node>().setColumn(x);
                n.GetComponent<Node>().setRow(z);

                mat[x, z] = n;
                int valor = m.matriz[z][x];

                if (valor == 0)
                {
                    n.GetComponent<Node>().convertToNormal();
                }else if(valor == 1)
                {
                    n.GetComponent<Node>().convertToObstacle();
                }
                else
                {
                    n.GetComponent<Node>().convertToSafeZone();
                }

                
               
                //Put the node onto the matrix, to keep track
                
            }
        }
        
    }

    void createEntitys()
    {
        CapsulaEntity listJSON = JsonConvert.DeserializeObject<CapsulaEntity>(entityData);

        Debug.Log(listJSON.listOfEntitys[0].id);

        for(int i = 0; i < listJSON.listOfEntitys.Length; i++)
        {

            GameObject e = Instantiate(enemy, new Vector3(listJSON.listOfEntitys[i].position[1] * (node.transform.localScale.x + nodeSeparation), 1f, listJSON.listOfEntitys[i].position[0] * -(node.transform.localScale.z + nodeSeparation)), Quaternion.identity);
           
            string type = listJSON.listOfEntitys[i].type;

            if (type == "spectre_gray"){
                e.GetComponent<Renderer>().material.color = spectreGray;
                
            }else if(type == "spectre_blue"){
                e.GetComponent<Renderer>().material.color = spectreBlue;
            }else if (type == "spectre_red"){
                e.GetComponent<Renderer>().material.color = spectreRed;
            }else if (type == "treasure"){
                e.GetComponent<Renderer>().material.color = treasure;
            }else if (type == "jarron"){
                e.GetComponent<Renderer>().material.color = jarron;
            }else if (type == "spectralEye"){
                e.GetComponent<Renderer>().material.color = spectralEye;
            }else if (type == "chuchu"){
                e.GetComponent<Renderer>().material.color = chuchu;
            }else if (type == "mouse"){
                e.GetComponent<Renderer>().material.color = mouse;
            }
            

            entitys.Add(e);

        }


    }

    void updateEntitys()
    {
        CapsulaEntity listJSON = JsonConvert.DeserializeObject<CapsulaEntity>(entityData);

        //Debug.Log(listJSON.listOfEntitys[0].id);
        //entitys[0].GetComponent<EnemyScript>().moveTo(Convert.ToSingle(listJSON.listOfEntitys[0].position[1] * (2.1)), Convert.ToSingle(listJSON.listOfEntitys[0].position[0] * -(2.1)));

        for (int i = 0; i < listJSON.listOfEntitys.Length; i++)
        {

            float moveRow = Convert.ToSingle(listJSON.listOfEntitys[i].position[1] * (2 + nodeSeparation));
            float moveColumn = Convert.ToSingle(listJSON.listOfEntitys[i].position[0] * -(2 + nodeSeparation));

            if (listJSON.listOfEntitys[i].type.Contains("spectre") || listJSON.listOfEntitys[i].type.Contains("mouse") || listJSON.listOfEntitys[i].type.Contains("chuchu"))
            {
                entitys[i].GetComponent<EnemyScript>().moveTo(moveRow, moveColumn);
            }

                //Comprobar si no se debe 

            
        

        }


    }

}
