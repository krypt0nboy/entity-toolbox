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
   *
   */
  protected function postSetClassType() {
    $classTypeInfo = entity_toolbox_class_type_get_info($this->classType);
    $this->__set('class_type_info', $classTypeInfo);
  }

  protected function postSetClassTypeInfo() {
    $classTypeTemplates = $this->classTypeInfo['default'];
    $flattened          = $this->flattenExtract('', 'class_default_', $classTypeTemplates);
    foreach ($flattened as $name => $value) {
      $this->updateTemplateVars($name, $value);
    }
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

  protected function initTemplateVars() {
    $baseClass = lowercase2camelcase($this->entityType);
    $this->updateTemplateVars('class_base_class', $baseClass);
  }
}