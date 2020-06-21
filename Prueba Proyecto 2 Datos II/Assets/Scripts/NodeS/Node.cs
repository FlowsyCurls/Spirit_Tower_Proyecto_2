using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Node : MonoBehaviour
{

    private int column;
    private int row;
    private bool isTraversable;

    public Color32 playerColor;
    public Color32 enemyColor;
    public float nodeObsAltitude;
    public float nodePathAltitude;

    // Start is called before the first frame update
    void Start()
    {
        isTraversable = true;
    }

    // Update is called once per frame
    void Update() {

        //Uptade state of the nodes
        updateNode();

    }
    // Triggers when a collision happen with this object, collision contains all info of the object that had collide with this object
    private void OnCollisionEnter(Collision collision)
    {
        Debug.Log("Column: " + column + " row: + " + row);
    }

    //Triggers when you click on the collider of the object, changes the state of the node, traversable or nor traversable (obstacle)
    private void OnMouseDown()
    {
        this.isTraversable = !this.isTraversable;
    }

    //Displays the color of the state of node, if is playerField (can walk)
    void updateNode() {

        //Set color if isPlayerField
        if (isTraversable)
        {
            this.GetComponent<Renderer>().material.color = playerColor;
            this.transform.localScale = new Vector3(transform.localScale.x, nodePathAltitude, transform.localScale.z);
        }
        //is enemy
        else
        {
            this.GetComponent<Renderer>().material.color = enemyColor;
            this.transform.localScale = new Vector3(transform.localScale.x, nodeObsAltitude, transform.localScale.z); 
        }

    }

    public void setColumn(int _column) {
        column = _column;
    }

    public void setRow(int _row)
    {
        row = _row;
    }

    public int getColumn()
    {
        return this.column;
    }

    public int getRow()
    {
        return this.row;
    }

}
