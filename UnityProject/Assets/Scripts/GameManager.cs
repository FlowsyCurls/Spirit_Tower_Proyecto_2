using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;



//Class that keeps the state of the game in the client side, tracks the player and enemy behavoir, sends data to server and call server petitions

public class GameManager : MonoBehaviour
{

    public GameObject node;
    public GameObject enemy;
    public GameObject client;
    public GameObject player;

    public int gridX;
    public int gridZ;
    public float nodeSeparation;

    public GameObject[,] mat;
    public int enemyQuantity;
    

    // Start is called before the first frame update
    void Start()
    {
        //Create the matrix
        mat = new GameObject[gridX, gridZ];     //Let a matrix of lenght nxm
        createGrid();       //Create all nodes on matrix, and put them onto the structure
        spawnEnemies();     //Spawn enemies on stage
        


    }

    // Update is called once per frame, keeps track of the player, at least at this early stage of the client-server communication
    void Update()
    {
        //If player is moving, send msg that he is moving
        if (player.GetComponent<PlayerMovement>().getLastDir() != player.GetComponent<PlayerMovement>().getDir()) {
            Debug.Log("Moviendose");
            //Send msg that the player is moving on a direction to server
            Program.Start();
            Program.sendMessage("Player is moving");
        }
    }


    //Creates all the nodes of the matrix and put them onto their respective position
    /*
    0 is the bottom left of the visualized matrix:
    
        ...
    [[0,1], [1,1]]
    [[0,0], [1,0]] ...
     
    */
    void createGrid() {

        for (int x = 0; x < gridX; x++)
        {
            for (int z = 0; z < gridZ; z++)
            {
                //Instantiate object, to create in map
                GameObject n = Instantiate(node, new Vector3(x * (node.transform.localScale.x + nodeSeparation), 0, z * (node.transform.localScale.z + nodeSeparation)), Quaternion.identity);

                //Get the script, and set their x and y values of the matrix

                n.GetComponent<Node>().setColumn(x);
                n.GetComponent<Node>().setRow(z);

                //Put the node onto the matrix, to keep track
                mat[x, z] = n;
            }
        }
        
    }

    //Spanwn an enemy on pos n,m

    void spawnEnemies() {

        for (int i = 0; i < enemyQuantity; i++)
        {
            GameObject fartestNode = mat[gridX - 1, gridZ - 1];        //Get the fartest node to spawn the enemies

            //Instantiate and set position for the enemy
            GameObject e = Instantiate(enemy, new Vector3(fartestNode.GetComponent<Node>().getColumn() * (node.transform.localScale.x + nodeSeparation), 2f, fartestNode.GetComponent<Node>().getRow() * (node.transform.localScale.z + nodeSeparation)), Quaternion.identity);
        }

    }

}
