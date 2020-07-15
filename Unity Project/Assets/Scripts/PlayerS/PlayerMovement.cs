using System.Data;
using UnityEngine;
using System.Collections.Generic;

public class PlayerMovement : MonoBehaviour
{

    public Color playerCol;
    public Color playerBlockingCol;

    public float speed;
    public float blockingSpeed;
    private float currentSpeed;
    private string dir;
    private string lastDir;
    public static int row;
    public static int column;
    public int lifes;
    public int score;

    public bool isBlocking;
    public bool hasFall;

    public IDictionary<string, string> enemiesDictionary = new Dictionary<string, string>()

    {
        {"Damage", "spectreGray spectreBlue spectreRed chuchu mouse"},
        //{"Neutral", "mouse"},
        {"Heal","jarron"}
    };
    // Start is called before the first frame update
    void Start()
    {
        //lifes = 5;
        //row = 0;
        //column = 0;
        //score = 0;
        dir = "none";
        lastDir = "none";
        hasFall = false;
        isBlocking = false;
    }



    // Update is called once per frame
    void Update()
    {
        //Checks if the speed limit is reached

        if (Input.GetKey(KeyCode.LeftShift))
        {
            currentSpeed = speed + 5f;
        }
        else
        {
            currentSpeed = speed;
        }

        //If the player fall because a trap, the z axis value is negative, this indicates that the player is dead
        if (this.transform.position.y < -5) {
            Debug.Log(" Caí en la trampa !!! ");
            lifes = 0;
            hasFall = true;
        }

        if (Input.GetKey(KeyCode.Q)) {
            Debug.Log(" Bloqueando");

            currentSpeed = blockingSpeed;
            this.GetComponent<Renderer>().material.color = playerBlockingCol;
            isBlocking = true;
        }
        if (Input.GetKeyUp(KeyCode.Q)) {
            Debug.Log("No Bloqueando");
            this.GetComponent<Renderer>().material.color = playerCol;
            currentSpeed = speed;
            isBlocking = false;
        }

        if (Input.GetKey(KeyCode.UpArrow))
            {
                //Move the Rigidbody forwards constantly at speed you define (the blue arrow axis in Scene view)
                setLastDir(dir);
                setDir("up");
                transform.localEulerAngles = new Vector3(0, 270, 0);
                transform.Translate(Vector3.forward * currentSpeed * Time.deltaTime,Space.World);

            }

            if (Input.GetKey(KeyCode.DownArrow))
            {
                //Move the Rigidbody backwards constantly at the speed you define (the blue arrow axis in Scene view)
                setLastDir(dir);
                setDir("down");
                transform.localEulerAngles = new Vector3(0, 90, 0);
                transform.Translate(-Vector3.forward * currentSpeed * Time.deltaTime, Space.World);
                
            }

            if (Input.GetKey(KeyCode.RightArrow))
            {
                setLastDir(dir);
                setDir("right");
                transform.localEulerAngles = new Vector3(0, 0, 0);
                transform.Translate(Vector3.right * currentSpeed * Time.deltaTime, Space.World);
            }

            if (Input.GetKey(KeyCode.LeftArrow))
            {
                setLastDir(dir);
                setDir("left");
                transform.localEulerAngles = new Vector3(0, 180, 0);
                transform.Translate(-Vector3.right * currentSpeed * Time.deltaTime, Space.World);
            }
            
    }

    private void OnCollisionEnter(Collision collision)
    {
        if (collision.collider.tag == "Enemy" && this.isBlocking == false) {

            if (collision.collider.GetComponent<EnemyScript>().id.Contains("spectre")) {
                this.lifes = 0;
            }

            else if (enemiesDictionary["Damage"].Contains(collision.collider.GetComponent<EnemyScript>().id))
            {
                this.lifes--;
            }
            else if (enemiesDictionary["Heal"].Contains(collision.collider.GetComponent<EnemyScript>().id))
            {
                Destroy(collision.collider.gameObject);
                this.lifes += 2;
                if (this.lifes > 5)
                    this.lifes = 5;
                this.score += 50;
            }


            //if (collision.collider.GetComponent<EnemyScript>().id.Contains("chuchu"))
            //{
            //    this.lifes--;
            //}
            //if (collision.collider.GetComponent<EnemyScript>().id.Contains("mouse"))
            //{
            //    this.lifes--;
            //}
            //Program.sendMessage("Pierdo vida, me quitaron " + this.lostLifes + " vidas");
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