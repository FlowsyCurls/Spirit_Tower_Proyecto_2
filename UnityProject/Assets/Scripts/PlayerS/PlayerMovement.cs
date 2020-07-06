using System.Data;
using UnityEngine;

public class PlayerMovement : MonoBehaviour
{

    public float speed;
    private string dir;
    private string lastDir;
    public static int row = 0;
    public static int column = 0;

    // Start is called before the first frame update
    void Start()
    {
        dir = "none";
        lastDir = "none";
    }

    // Update is called once per frame
    void FixedUpdate()
    {
        //Checks if the speed limit is reached

        if (Input.GetKey(KeyCode.Space))
        {
            speed = 10f;
        }
        else
        {
            speed = 4f;
        }        

        if (Input.GetKey(KeyCode.UpArrow))
            {
                //Move the Rigidbody forwards constantly at speed you define (the blue arrow axis in Scene view)
                setLastDir(dir);
                setDir("up");
            
                transform.Translate(transform.forward * speed * Time.deltaTime);

            }

            if (Input.GetKey(KeyCode.DownArrow))
            {
                //Move the Rigidbody backwards constantly at the speed you define (the blue arrow axis in Scene view)
                setLastDir(dir);
                setDir("down");
                transform.Translate(-transform.forward * speed * Time.deltaTime);
                
            }

            if (Input.GetKey(KeyCode.RightArrow))
            {
                setLastDir(dir);
                setDir("right");
                transform.Translate(transform.right * speed * Time.deltaTime);
            }

            if (Input.GetKey(KeyCode.LeftArrow))
            {
                setLastDir(dir);
                setDir("left");
                transform.Translate(-transform.right * speed * Time.deltaTime);
            }
            
    }

    private void setDir(string _dir) {
        dir = _dir;
    }

    public string getDir() {
        return dir;
    }

    private void setLastDir(string _dir)
    {
        lastDir = _dir;
    }

    public string getLastDir()
    {
        return lastDir;
    }


}