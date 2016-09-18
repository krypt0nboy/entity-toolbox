<?php

/**
 * Class EntityToolboxInfoClassesModel
 */
class EntityToolboxInfoClassesModel extends EntityToolboxInfoRecursiveModel {
  /**
   * @access protected
   * @var array $classTypesInfo
   *   The class types info.
   *
   * @see hook_class_type_info().
   */
  protected $classTypesInfo = array();

  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = $this->mergeConstructArgs(
      array(
        'self_key'  => 'classes',
        'structure' => array(
          'entity'        => array(
            'type'   => 'array',
            'method' => 'buildEntityClass',
            'model'  => 'entity_toolbox_info_classes_class'
          ),
          'controller'    => array(
            'type'   => 'array',
            'method' => 'buildControllerClass',
            'model'  => 'entity_toolbox_info_classes_class'
          ),
          'ui controller' => array(
            'type'   => 'array',
            'method' => 'buildUIControllerClass',
            'model'  => 'entity_toolbox_info_classes_class'
          ),
        )
      ),
      $args
    );
    parent::__construct($args);
  }
}