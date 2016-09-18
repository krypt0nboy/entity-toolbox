<?php

/**
 * Class ClassBuilder
 */
class EntityToolboxInfoClassesClassBuilder extends EntityToolboxInfoKeyBuilder {
  /**
   * @var string $classType
   *   The class type.
   */
  protected $classType;
  /**
   * @var array $classTypeInfo
   *   The class type info.
   */
  protected $classTypeInfo = array();
  /**
   * @var string $baseClass
   *   The base class name.
   */
  protected $baseClass;

  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = $this->mergeConstructArgs(
      array(
        'parent_key'  => 'classes',
        'model_class' => 'EntityToolboxInfoClassesClassModel',
      ),
      $args
    );
    parent::__construct($args);
  }

  /**
   * @return string
   */
  public function getClassType() {
    return $this->classType;
  }

  /**
   * @param string $classType
   */
  public function setClassType($classType) {
    $this->classType = $classType;
  }

  /**
   * After class type has been set.
   */
  protected function postSetClassType() {
    $classTypeInfo = entity_toolbox_class_type_get_info($this->classType);
    $this->__set('class_type_info', $classTypeInfo);
  }

  /**
   * @return array
   */
  public function getClassTypeInfo() {
    return $this->classTypeInfo;
  }

  /**
   * @param array $classTypeInfo
   */
  public function setClassTypeInfo($classTypeInfo) {
    $this->classTypeInfo = $classTypeInfo;
  }

  /** {{@inheritdoc}} */
  protected function initTemplateVars(array $vars = array()) {
    $vars += $this->flattenExtract('', 'class_default_', $this->classTypeInfo['default']);
    $vars += array('class_base_class' => $this->baseClass);
    parent::initTemplateVars($vars);
  }
}