<?php

/**
 * Class FactoryBase
 */
class FactoryBase {

  use EntityToolboxCommonTraits, TemplatingTraits;

  /**
   * @var string $name
   */
  protected $name;
  /**
   * @var string $baseClass
   */
  protected $baseClass;
  /**
   * @var array $classInfo
   */
  protected $classInfo = array();
  /**
   * @var string $modelClass
   */
  protected $modelClass;
  /**
   * @var string $parsedModel
   */
  protected $parsedModelClass;
  /**
   * @var array $instanceArgs
   */
  protected $instanceArgs = array();

  /**
   * FactoryBase constructor.
   *
   * @param array $args
   */
  public function __construct(array $args = array()) {
    $this->constructSet($args);
    $this->initTemplateVars();
  }

  /**
   * @param $args
   */
  protected function constructSet(array $args = array()) {
    $this->setConstructArgs($args);
    foreach ($args as $argName => $arg) {
      $this->__set($argName, $arg);
    }
  }

  /**
   * @return string
   */
  public function getName() {
    return $this->name;
  }

  /**
   * @param string $name
   */
  public function setName($name) {
    $this->name = $name;
  }

  /**
   * @return string
   */
  public function getBaseClass() {
    return $this->baseClass;
  }

  /**
   * @param string $baseClass
   */
  public function setBaseClass($baseClass) {
    $this->baseClass = $baseClass;
  }

  /**
   * @return array
   */
  public function getClassInfo() {
    return $this->classInfo;
  }

  /**
   * @param array $classInfo
   */
  public function setClassInfo($classInfo) {
    $this->classInfo = $classInfo;
  }

  /**
   * @return string
   */
  public function getModelClass() {
    return $this->modelClass;
  }

  /**
   * @param string $modelClass
   */
  public function setModelClass($modelClass) {
    $this->modelClass = $modelClass;
  }

  /**
   * @return string
   */
  public function getParsedModelClass() {
    return $this->parsedModelClass;
  }

  /**
   * @param string $parsedModelClass
   */
  public function setParsedModelClass($parsedModelClass) {
    $this->parsedModelClass = $parsedModelClass;
  }

  /**
   * @return array
   */
  public function getInstanceArgs() {
    return $this->instanceArgs;
  }

  /**
   * @param array $instanceArgs
   */
  public function setInstanceArgs($instanceArgs) {
    $this->instanceArgs = $instanceArgs;
  }

  protected function initTemplateVars() {

  }

  /**
   * Parses the class model to get the right object class.
   */
  protected function parseClassModel() {
    if (isset($this->modelClass)) {
      $parsed = $this->processValueTemplate($this->modelClass);
      $parsed = $this->isValueTemplate($parsed) ? $this->baseClass : $parsed;
      $this->__set('parsed_model_class', $parsed);
    }
    else {
      $this->__set('parsed_model_class', $this->baseClass);
    }
  }

  /**
   * @param $value
   * @return string
   */
  protected function processValueTemplate($value) {
    return $this->isValueTemplate($value) ? string_template_process($value, $this->getTemplateVars()) : $value;
  }

  /**
   * Returns a property type instance.
   *
   * @return EntityToolboxPropertyBase
   */
  public function getInstance() {
    $this->parseClassModel();
    $class        = $this->getParsedModelClass();
    $class        = class_exists($class) ? $class : $this->baseClass;
    $instanceArgs = $this->getInstanceArgs();

    return new $class($instanceArgs);
  }

}