<?php

/**
 * Class EntityToolboxInfoClassesClassModel
 */
class EntityToolboxInfoClassesClassModel extends EntityToolboxInfoRecursiveModel {
  /**
   * @access protected
   * @var string $classType
   *   The class type.
   *
   * @see hook_class_type_info().
   */
  protected $classType;
  /**
   * @access protected
   * @var array $classTypeInfo
   *   The class type info.
   *
   * @see hook_class_type_info().
   */
  protected $classTypeInfo = array();

  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = $this->mergeConstructArgs(
      array(
        'parent_key' => 'classes',
        'structure'  => array(
          'class' => array(
            'type'    => 'string',
            'default' => '%class_default_class%',
          ),
          'path'  => array(
            'type'    => 'string',
            'default' => '%class_default_path%',
            'model'   => ''
          ),
          'file'  => array(
            'type'    => 'string',
            'default' => '%class_default_file%',
          ),
        )
      ),
      $args
    );
    parent::__construct($args);
  }

  /**
   * Getter for "classType".
   *
   * @return string
   */
  public function getClassType() {
    return $this->classType;
  }

  /**
   * Setter for "classType".
   *
   * @param string $classType
   *   The class type.
   */
  public function setClassType($classType) {
    $this->classType = $classType;
  }

  /**
   * Getter for "classTypeInfo".
   *
   * @return array
   */
  public function getClassTypeInfo() {
    return $this->classTypeInfo;
  }

  /**
   * Setter for "classTypeInfo".
   *
   * @param array $classTypeInfo
   *   The class type info to set.
   */
  public function setClassTypeInfo($classTypeInfo) {
    $this->classTypeInfo = $classTypeInfo;
  }
}