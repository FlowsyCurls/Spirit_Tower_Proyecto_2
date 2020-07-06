using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EnemyScript : MonoBehaviour
{
    // Start is called before the first frame update

    public float row;
    public float column;

    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {

    }
    public void moveTo(float _row, float _column)
    {

        if (_row != row || _column != column)
        {
            Debug.Log("ME MOVIIIIIIIII");
            row = _row;
            column = _column;
            this.transform.localPosition = new Vector3(row, 1f, column);
        }
    }
}
