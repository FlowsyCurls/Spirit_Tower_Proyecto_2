using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Node : MonoBehaviour
{

    private int column;
    private int row;
    private bool isTraversable;
    private bool isTrap;
    public String type;

    public Color32 normalCellColor;
    public Color32 obstacleCellColor;
    public Color32 safeZoneCellColor;
    public float nodeObsAltitude;
    public float nodePathAltitude;

    // Start is called before the first frame update
    void Start()
    {

    }

    // Update is called once per frame
    void Update() {


    }
    // Triggers when a collision happen with this object, collision contains all info of the object that had collide with this object
    private void OnCollisionEnter(Collision collision)
    {
        if(collision.gameObject.name == "Player")
        {
            PlayerMovement.row = row;
            PlayerMovement.column = column;

            if (this.isTrap) {
                Debug.Log("Me destruyo!!!");
                Destroy(this.GetComponent<GameObject>());
            }
        }
        //Debug.Log("Column: " + column + " row: + " + row);
    }

    //Triggers when you click on the collider of the object, changes the state of the node, traversable or nor traversable (obstacle)
    private void OnMouseDown()
    {
        //convertToSafeZone();
    }

    public void convertToNormal()
    {
        isTraversable = true;
        this.GetComponent<Renderer>().material.color = normalCellColor;
        type = "normal";

    }

    public void convertToObstacle()
    {
        this.isTraversable = false;
        this.GetComponent<Renderer>().material.color = obstacleCellColor;
        this.transform.localScale = new Vector3(transform.localScale.x, 2, transform.localScale.z);
        this.transform.localPosition = new Vector3(transform.localPosition.x, nodeObsAltitude, transform.localPosition.z);
        type = "obstacle";
    }

    public void convertToSafeZone()
    {
        this.isTraversable = true;
        this.GetComponent<Renderer>().material.color = safeZoneCellColor;
        this.transform.localScale = new Vector3(transform.localScale.x, nodePathAltitude, transform.localScale.z);
    }

    public void convertToTrap()
    {
        this.isTraversable = true;
        this.isTrap = true;
        Destroy(this.GetComponent<Collider>());
        this.GetComponent<Renderer>().material.color = normalCellColor;
        this.transform.localScale = new Vector3(transform.localScale.x, nodePathAltitude, transform.localScale.z);
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
