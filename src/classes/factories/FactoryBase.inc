<?php

/**
 * Class FactoryBase
 */
class FactoryBase {
  /**
   * @var string $name
   */
  protected $name;
  /**
   * @var array $factoryInfo
   */
  protected $factoryInfo = array();
  /**
   * @var string $baseClass
   */
  protected $baseClass;
  /**
   * @var array $args
   */
  protected $args = array();
  /**
   * @var string $parsedModel
   */
  protected $parsedModel;

  /**
   * FactoryBase constructor.
   *
   * @param string $name
   * @param array  $args
   */
  public function __construct($name, array $args = array()) {
    $this->name = $name;
    $this->setFactoryInfo();
    $this->baseClass = $this->factoryInfo['base class'];
    $this->setArgs($args);
  }

  /**
   * Sets the class info.
   */
  protected function setFactoryInfo() {
  }

  /**
   * Setter for $args.
   *
   * @param array $args
   *   The parsing args.
   */
  protected function setArgs(array $args = array()) {
    $this->args = $args;
  }

  /**
   * Parses the class model to get the right object class.
   */
  protected function parseClassModel() {
    $this->parsedModel = string_template_process($this->factoryInfo['model class'], $this->args);
  }

  /**
   * Returns the parsed class.
   */
  protected function getParsedModel() {
    return $this->parsedModel;
  }

  /**
   * Returns an instance of the target class.
   *
   */
  public function getInstance() {
  }

}