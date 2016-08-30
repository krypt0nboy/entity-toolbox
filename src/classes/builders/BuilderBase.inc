<?php

/**
 * Class BuilderBase
 *
 * Base class to build data required by drupal available api's.
 */
class BuilderBase {

  use EntityToolboxCommonTraits, TemplatingTraits;

  /**
   * @var string $modelClass
   */
  protected $modelClass;
  /**
   * @var ModelBase $model
   *   The data model.
   */
  protected $model;
  /**
   * @var array $structure
   *   The structure of the array to build.
   */
  protected $structure = array();
  /**
   * @var array $processedData
   *   The built/rebuilt data.
   */
  protected $processedData = array();
  /**
   * @var array $build
   */
  protected $build = array();
  /**
   * @var BuilderBase[] $keyBuilders
   *   The structure keys builders.
   */
  protected $keyBuilders = array();
  /**
   * @var array $keyBuildersClasses
   *   An array of key builder classes.
   */
  protected $keyBuildersClasses = array();

  /**
   * BuilderBase constructor.
   *
   * @param array $args
   *   The properties to set.
   *
   * @throws EntityToolboxException
   */
  public function __construct(array $args = array()) {
    $this->constructSet($args);
  }

  /**
   * @param $args
   */
  protected function constructSet($args) {
    $this->setConstructArgs($args);
    foreach ($args as $argName => $arg) {
      $this->__set($argName, $arg);
    }
    $this->initTemplateVars();
  }

  /**
   * @return array
   */
  protected function initTemplateVars() {

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
  protected function setModelClass($modelClass) {
    $this->modelClass = $modelClass;
  }

  /**
   *
   */
  protected function postSetModelClass() {
    $model = $this->modelGetInstance($this->modelClass);
    $this->__set('model', $model);
  }

  /**
   * @return ModelBase
   */
  public function getModel() {
    return $this->model;
  }

  /**
   * @param ModelBase $model
   */
  protected function setModel($model) {
    $this->model = $model;
  }

  /**
   *
   */
  protected function postSetModel() {
    $this->__set('structure', $this->getModel()->getStructure());
  }

  /**
   * @param $modelClass
   * @param $args
   *
   * @return ModelBase
   */
  protected function modelGetInstance($modelClass, array $args = array()) {
    return new $modelClass($args);
  }

  /**
   * Gets the data structure.
   *
   * @param string $key
   *   A key.
   *
   * @return array
   */
  public function getStructure($key = NULL) {
    return isset($key) ? $this->structure[$key] : $this->structure;
  }

  /**
   * @param array $structure
   */
  protected function setStructure(array $structure = array()) {
    foreach ($structure as $key => $params) {
      $this->structure[$key] = $params;
    }
  }

  /**
   *
   */
  protected function prepareStructure() {

  }

  /**
   * @param null $key
   * @return array
   */
  public function getProcessedData($key = NULL) {
    return isset($key) ? $this->processedData[$key] : $this->processedData;
  }

  /**
   * @param array $processedData
   */
  protected function setProcessedData($processedData) {
    $this->processedData = $processedData;
  }

  /**
   * @return array
   */
  public function getBuild($key) {
    return isset($key) ? $this->build[$key] : $this->build;
  }

  /**
   * @param array $build
   */
  public function setBuild($build) {
    $this->build = $build;
  }

  /**
   * @param $key
   * @param $build
   *
   * @return array
   */
  protected function setKeyBuild($key, $build) {
    $this->build[$key] = $this->validateKeyBuild($key, $build);

    return $this->build[$key];
  }

  /**
   * Sets a single value structure and build parameters.
   *
   * @param string $key
   *   The key within the array.
   * @param array  $params
   *   The build parameters.
   *   An array whose values are :
   *    - type : (optional) The key php var type.
   *      (Eg : "string", "array", "numeric", etc...)
   *    - method : (optional) The class method used to build the value.
   *    - default : (optional) The default value. Can be a template to be processed by string_process_template().
   *    - model : (optional) The sub model.
   *    Make sure not to have conflicts in your building parameters.
   *    (Eg : can't use a builder if you have a default value).
   */
  protected function setKeyParams($key, array $params = array()) {
    $this->structure[$key] = $params;
  }

  /**
   * @return BuilderBase[]
   */
  public function getKeyBuilders() {
    return $this->keyBuilders;
  }

  /**
   * @param $key
   * @return \BuilderBase
   */
  public function getKeyBuilder($key) {
    return $this->keyBuilders[$key];
  }

  /**
   * @param BuilderBase[] $keyBuilders
   */
  protected function setKeyBuilders($keyBuilders) {
    foreach ($keyBuilders as $key => $keyBuilder) {
      $this->setKeyBuilder($key, $keyBuilder);
    }
  }

  /**
   * Sets the builder for a given key.
   *
   * @param string            $key
   *   The key name.
   * @param \BuilderBase|NULL $builder
   *   The builder.
   */
  protected function setKeyBuilder($key, BuilderBase $builder = NULL) {
    $this->keyBuilders[$key] = $builder;
  }

  /**
   * @return array
   */
  public function getKeyBuildersClasses() {
    return $this->keyBuildersClasses;
  }

  /**
   * @param array $keyBuildersClasses
   */
  protected function setKeyBuildersClasses($keyBuildersClasses) {
    $this->keyBuildersClasses = $keyBuildersClasses;
  }

  /**
   *
   */
  protected function postSetKeyBuildersClasses() {
    $this->autoSetKeyBuilders();
  }

  /**
   * Sets the key builders from the keybuilders classes.
   */
  public function autoSetKeyBuilders() {
    foreach ($this->getKeyBuildersClasses() as $key => $keyBuildersClass) {
      $this->setKeyBuilder($key, $this->keyBuilderGetInstance($keyBuildersClass));
    }
  }

  /**
   * @param $keyBuilderClass
   * @param $args
   *
   * @return mixed
   */
  protected function keyBuilderGetInstance($keyBuilderClass, array $args = array()) {
    $args = $this->mergeConstructArgs(array(
      'parent_builder' => $this,
    ), $args);

    return new $keyBuilderClass($args);
  }

  /**
   * Builds the value for a given key.
   *
   * @param string $key
   *   The key to build.
   *
   * @return mixed
   */
  protected function buildKey($key) {
    if (!empty($this->structure[$key]['method'])) {
      $method = $this->structure[$key]['method'];
      $build  = $this->$method();
      if (is_null($build) && isset($this->structure[$key]['default'])) {
        return $this->buildKeyDefault($key);
      }
      else {
        return $this->setKeyBuild($key, $build);
      }
    }
    else {
      if (isset($this->structure[$key]['default'])) {
        return $this->buildKeyDefault($key);
      }
    }
  }

  /**
   * Default build method for a given key.
   *
   * @param string $key
   *   The key name.
   *
   * @return mixed
   */
  protected function buildKeyDefault($key) {
    $default = $this->structure[$key]['default'];
    $build   = $this->processValueTemplate($default);

    return $this->setKeyBuild($key, $build);
  }

  /**
   * @param $key
   */
  protected function postBuildKey($key) {
    $uKey   = lowercase2camelcase($key);
    $method = "postBuild$uKey";
    if (method_exists($this, $method)) {
      $this->$method($uKey);
    }
  }

  /**
   * Return the built/rebuilt data.
   *
   * @return array
   */
  public function build() {
    return $this->buildDefault();
  }

  /**
   * Default build function.
   *
   * @return array
   */
  protected function buildDefault() {
    $build = array();
    foreach (array_keys($this->structure) as $key) {
      $build[$key] = $this->buildKey($key);
    }

    return $build;
  }

  /**
   * @param $value
   * @return string
   */
  protected function processValueTemplate($value) {
    return $this->isValueTemplate($value) ? string_template_process($value, $this->getTemplateVars()) : $value;
  }

  /**
   * Validates a key build.
   *
   * @param string $key
   *   The key.
   * @param mixed  $build
   *   The build to validate.
   *
   * @return bool
   */
  protected function validateKeyBuild($key, $build) {
    switch ($this->getStructure($key)['type']) {
      case 'boolean':
        if (!is_bool($build)) {
          settype($build, 'boolean');
        }
        break;
      case 'integer':
        if (!is_integer($build)) {
          settype($build, 'integer');
        }
        break;
      case 'float':
        if (!is_null($build)) {
          if (!is_float($build)) {
            settype($build, 'float');
          }
        }
        else {
          settype($build, 'null');
        }
        break;
      case 'string':
        if ($this->isValueTemplate($build)) {
          $build = NULL;
        }
        break;
      case 'array':
        if (!is_array($build)) {
          $build = array();
        }
        break;
      case 'object':
        break;
      case 'null':
        break;
      default:
        break;
    }

    $cKey   = lowercase2camelcase($key);
    $method = 'validate' . $cKey;
    if (method_exists($this, $method)) {
      $build = $this->$method($build);
    }

    return $build;
  }
}